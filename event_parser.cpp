/*

Event parser.

Copyright (C) 2014 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Revision: 6027 $ $Date:: 2017-03-14 #$ $Author: serge $

#include "event_parser.h"       // self

#include <iostream>             // cerr

#include "events.h"                 // Event
#include "../utils/tokenizer.h"     //

NAMESPACE_SKYPE_SERVICE_START

#define KEYW_CONNSTATUS             "CONNSTATUS"
#define KEYW_CURRENTUSERHANDLE      "CURRENTUSERHANDLE"
#define KEYW_USERSTATUS             "USERSTATUS"
#define KEYW_CALL                   "CALL"
#define KEYW_VOICEMAIL              "VOICEMAIL"
#define KEYW_CHAT                   "CHAT"
#define KEYW_CHATMEMBER             "CHATMEMBER"
#define KEYW_DURATION               "DURATION"
#define KEYW_ERROR                  "ERROR"
#define KEYW_PSTN_STATUS            "PSTN_STATUS"
#define KEYW_STATUS                 "STATUS"
#define KEYW_FAILUREREASON          "FAILUREREASON"
#define KEYW_ALTER                  "ALTER"
#define KEYW_SET_INPUT              "SET_INPUT"
#define KEYW_SET_OUTPUT             "SET_OUTPUT"
#define KEYW_FILE                   "file"
#define KEYW_VAA_INPUT_STATUS       "VAA_INPUT_STATUS"
#define KEYW_TRUE                   "TRUE"
#define KEYW_FALSE                  "FALSE"
#define KEYW_USER                   "USER"

Event* EventParser::to_event( const std::string & s )
{
    Tokenized toks;

    toks.str    = s;
    tokenize_to_vector( toks.tokens, s, " " );

    return handle_tokens( toks );
}

std::string & join_tokens( std::string & res, const std::vector< std::string > & toks, int start_position )
{
    int size = (int) toks.size();

    if( size <= start_position )
        return res;

    for( int i = start_position; i < size; ++i )
    {
        if( i != start_position )
        {
            res.append( " " );
        }

        res.append( toks[i] );
    }

    return res;
}


/**
 * @param s original string
 */
Event* EventParser::handle_tokens( Tokenized & toks )
{
    try
    {
        return handle_tokens__throwing( toks );
    }
    catch( std::exception &e )
    {
        std::cerr << "exception - " << e.what() << std::endl;
    }

    return nullptr;
}

void EventParser::get_keyw_and_command_id( Tokenized & tok, std::string & keyw, uint32_t & id )
{
    id  = 0;

    if( tok.tokens[0].empty() )
        return;

    if( tok.tokens[0][0] == '#' )
    {
        id = std::stoi( tok.tokens[0].substr( 1 ) );
        tok.tokens.erase( tok.tokens.begin() );
    }

    if( tok.tokens.empty() )
        return;

    keyw    = tok.tokens[0];
}

Event* EventParser::create_unknown( const std::string & keyw, const Tokenized & toks, uint32_t req_id )
{
    return new UnknownEvent( keyw + ": " + toks.str, req_id );
}

Event* EventParser::handle_tokens__throwing( Tokenized & toks )
{
    if( toks.tokens.empty() )
        return new UnknownEvent( toks.str, 0 );

    std::string keyw;
    uint32_t req_id;
    get_keyw_and_command_id( toks, keyw, req_id );

    if( keyw == KEYW_CONNSTATUS )
    {
        return handle_connstatus( toks, req_id );
    }
    else if( keyw == KEYW_USERSTATUS )
    {
        return handle_userstatus( toks, req_id );
    }
    else if( keyw == KEYW_CURRENTUSERHANDLE )
    {
        return handle_currentuserhandle( toks, req_id );
    }
    else if( keyw == KEYW_CALL )
    {
        return handle_call( toks, req_id );
    }
    else if( keyw == KEYW_VOICEMAIL )
    {
        return handle_voicemail( toks, req_id );
    }
    else if( keyw == KEYW_ERROR )
    {
        return handle_error( toks, req_id );
    }
    else if( keyw == KEYW_CHAT )
    {
        return handle_chat( toks, req_id );
    }
    else if( keyw == KEYW_CHATMEMBER )
    {
        return handle_chatmember( toks, req_id );
    }
    else if( keyw == KEYW_USER )
    {
        return handle_user( toks, req_id );
    }
    else if( keyw == KEYW_ALTER )
    {
        if( toks.tokens.size() < 2 )
            return create_unknown( "not enough tokens (<2)", toks, req_id );

        if( toks.tokens[1] != KEYW_CALL )
            return create_unknown( toks.tokens[1], toks, req_id );

        return handle_alter_call( toks, req_id );
    }

    return create_unknown( keyw, toks, req_id );

}

Event* EventParser::handle_connstatus( const Tokenized & toks, uint32_t req_id )
{
    if( toks.tokens.size() != 2 )
        throw WrongFormat( "expected 2 token(s)" );

    conn_status_e c = to_conn_status( toks.tokens[1] );

    return new ConnStatusEvent( c, req_id );
}
Event* EventParser::handle_userstatus( const Tokenized & toks, uint32_t req_id )
{
    if( toks.tokens.size() != 2 )
        throw WrongFormat( "expected 2 token(s)" );

    user_status_e c = to_user_status( toks.tokens[1] );

    return new UserStatusEvent( c, req_id );
}
Event* EventParser::handle_currentuserhandle( const Tokenized & toks, uint32_t req_id )
{
    if( toks.tokens.size() != 2 )
        throw WrongFormat( "expected 2 token(s)" );

    const std::string & s = toks.tokens[1];

    return new CurrentUserHandleEvent( s, req_id );
}
Event* EventParser::handle_call( const Tokenized & toks, uint32_t req_id )
{
    if( toks.tokens.size() < 4 )
        throw WrongFormat( "expected at least 4 token(s)" );

    if( toks.tokens[1].empty() )
        throw WrongFormat( "CALL_ID is not defined" );

    uint32_t call_id = std::stoul( toks.tokens[1] );

    const std::string keyw2 = toks.tokens[2];

    if( keyw2 == KEYW_DURATION )
    {
        if( toks.tokens[3].empty() )
            throw WrongFormat( "DURATION is empty" );

        uint32_t dur = std::stoul( toks.tokens[3] );

        return new CallDurationEvent( call_id, dur, req_id );
    }
    else if( keyw2 == KEYW_STATUS )
    {
        if( toks.tokens[3].empty() )
            throw WrongFormat( "STATUS is empty" );

        call_status_e s = to_call_status( toks.tokens[3] );

        return new CallStatusEvent( call_id, s, req_id );
    }
    else if( keyw2 == KEYW_PSTN_STATUS )
    {
        if( toks.tokens[3].empty() )
            throw WrongFormat( "PSTN_STATUS is empty" );

        uint32_t error = std::stoul( toks.tokens[3] );

        std::string descr;

        join_tokens( descr, toks.tokens, 4 );

        return new CallPstnStatusEvent( call_id, error, descr, req_id );
    }
    else if( keyw2 == KEYW_VAA_INPUT_STATUS )
    {
        if( toks.tokens[3].empty() )
            throw WrongFormat( "VAA_INPUT_STATUS is empty" );


        if( toks.tokens[3] != KEYW_TRUE && toks.tokens[3] != KEYW_FALSE )
            throw WrongFormat( "VAA_INPUT_STATUS should be TRUE or FALSE" );

        uint32_t s = ( toks.tokens[3] == KEYW_TRUE ) ? 1 : 0;

        return new CallVaaInputStatusEvent( call_id, s, req_id );
    }
    else if( keyw2 == KEYW_FAILUREREASON )
    {
        if( toks.tokens[3].empty() )
            throw WrongFormat( "FAILUREREASON is empty" );

        uint32_t c = std::stoul( toks.tokens[3] );

        return new CallFailureReasonEvent( call_id, c, req_id );
    }

    return new UnknownEvent( keyw2 + ": " + toks.str, req_id );
}

Event* EventParser::handle_voicemail( const Tokenized & toks, uint32_t req_id )
{
    if( toks.tokens.size() < 3 )
        throw WrongFormat( "expected at least 3 token(s)" );

    if( toks.tokens[1].empty() )
        throw WrongFormat( "CALL_ID is not defined" );

    uint32_t call_id = std::stoul( toks.tokens[1] );

    const std::string keyw2 = toks.tokens[2];

    if( keyw2 == KEYW_DURATION )
    {
        if( toks.tokens[3].empty() )
            throw WrongFormat( "DURATION is empty" );

        uint32_t dur = std::stoul( toks.tokens[3] );

        return new VoicemailDurationEvent( call_id, dur, req_id );
    }

    return new UnknownEvent( keyw2 + ": " + toks.str, req_id );
}

Event* EventParser::handle_error( const Tokenized & toks, uint32_t req_id )
{
    if( toks.tokens.size() < 2 )
        throw WrongFormat( "expected at least 2 token(s)" );

    uint32_t error = std::stoul( toks.tokens[1] );

    std::string descr;

    join_tokens( descr, toks.tokens, 2 );

    return new ErrorEvent( error, descr, req_id );
}

Event* EventParser::handle_alter_call( const Tokenized & toks, uint32_t req_id )
{
    // ALTER CALL 846 SET_INPUT file="c:\test.wav"

    if( toks.tokens.size() < 5 )
        throw WrongFormat( "expected at least 5 token(s)" );

    if( toks.tokens[2].empty() )
        throw WrongFormat( "CALL_ID is not defined" );

    uint32_t call_id = std::stoul( toks.tokens[2] );

    std::vector< std::string > pars;
    tokenize_to_vector( pars, toks.tokens[4], "=" );

    if( toks.tokens[3] == KEYW_SET_INPUT || toks.tokens[3] == KEYW_SET_OUTPUT )
    {
        bool is_input = ( toks.tokens[3] == KEYW_SET_INPUT );

        if( pars.size() != 2 )
            throw WrongFormat( "badly formed parameters - " + toks.tokens[4] );

        if( pars[0] == KEYW_FILE )
        {
            if( is_input )
                return new AlterCallSetInputFileEvent( call_id, pars[1], req_id );
            else
                return new AlterCallSetOutputFileEvent( call_id, pars[1], req_id );
        }
    }

    return create_unknown( toks.tokens[3], toks, req_id );
}

Event* EventParser::handle_chat( const Tokenized & toks, uint32_t req_id )
{
    return new ChatEvent( req_id );
}

Event* EventParser::handle_chatmember( const Tokenized & toks, uint32_t req_id )
{
    return new ChatMemberEvent( req_id );
}

Event* EventParser::handle_user( const Tokenized & toks, uint32_t req_id )
{
    return new UserEvent( req_id );
}

NAMESPACE_SKYPE_SERVICE_END

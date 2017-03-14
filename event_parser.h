/*

Event* parser.

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

#ifndef EVENT_PARSER_H
#define EVENT_PARSER_H

#include <string>                   // std::string
#include <vector>                   // std::vector
#include <stdexcept>                // std::runtime_error

#include "namespace_lib.h"          // NAMESPACE_SKYPE_SERVICE_START

NAMESPACE_SKYPE_SERVICE_START

class Event;

class EventParser
{
    struct Tokenized
    {
        std::string                 str;
        std::vector< std::string >  tokens;
    };

public:
    struct WrongFormat: public std::runtime_error
    {
        WrongFormat( const std::string & str ):
            std::runtime_error( str )
        {}
    };

public:
    static Event* to_event( const std::string & s );

private:

    static Event* create_unknown( const std::string & keyw, const Tokenized & toks, uint32_t req_id );

    static Event* handle_tokens( Tokenized & toks );

    static Event* handle_tokens__throwing( Tokenized & toks );
    static void get_keyw_and_command_id( Tokenized & toks, std::string & keyw, uint32_t & id );

    static Event* handle_connstatus( const Tokenized & toks, uint32_t req_id );
    static Event* handle_userstatus( const Tokenized & toks, uint32_t req_id );
    static Event* handle_currentuserhandle( const Tokenized & toks, uint32_t req_id );
    static Event* handle_error( const Tokenized & toks, uint32_t req_id );
    static Event* handle_call( const Tokenized & toks, uint32_t req_id );
    static Event* handle_voicemail( const Tokenized & toks, uint32_t req_id );
    static Event* handle_alter_call( const Tokenized & toks, uint32_t req_id );
    static Event* handle_chat( const Tokenized & toks, uint32_t req_id );
    static Event* handle_chatmember( const Tokenized & toks, uint32_t req_id );
    static Event* handle_user( const Tokenized & toks, uint32_t req_id );
};

NAMESPACE_SKYPE_SERVICE_END

#endif  // EVENT_PARSER_H

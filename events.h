/*

Event.

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

// $Revision: 4819 $ $Date:: 2016-10-13 #$ $Author: serge $

#ifndef SKYPE_SERVICE_EVENTS_H
#define SKYPE_SERVICE_EVENTS_H

#include <string>                   // std::string

#include "parser_types.h"           // user_status_e, conn_status_e, call_status_e

#include "namespace_lib.h"          // NAMESPACE_SKYPE_SERVICE_START

NAMESPACE_SKYPE_SERVICE_START

struct Event
{
    Event( uint32_t            req_id ):
        req_id( req_id )
    {
    }

    virtual ~Event() {}

    uint32_t        req_id;
};

struct UnknownEvent: public Event
{
    UnknownEvent(
        const std::string   & descr,
        uint32_t            req_id ):
            Event( req_id ),
            descr( descr )
    {
    }

    std::string         descr;
};

struct BasicCallEvent: public Event
{
    BasicCallEvent(
        uint32_t            call_id,
        uint32_t            req_id ):
            Event( req_id ),
            call_id( call_id )
    {
    }

    uint32_t          call_id;
};

struct ErrorEvent: public Event
{
    ErrorEvent(
        uint32_t            error_code,
        const std::string   & descr,
        uint32_t            req_id ):
            Event( req_id ),
            error_code( error_code ),
            descr( descr )
    {
    }

    uint32_t            error_code;
    std::string         descr;
};

struct ConnStatusEvent: public Event
{
    ConnStatusEvent(
        conn_status_e       conn_s,
        uint32_t            req_id ):
        Event( req_id ),
        status( conn_s )
    {
    }

    conn_status_e   status;
};

struct UserStatusEvent: public Event
{
    UserStatusEvent(
        user_status_e       user_s,
        uint32_t            req_id ):
        Event( req_id ),
        status( user_s )
    {
    }

    user_status_e   status;
};

struct CurrentUserHandleEvent: public Event
{
    CurrentUserHandleEvent(
        const std::string   & user_handle,
        uint32_t            req_id ):
            Event( req_id ),
            user_handle( user_handle )
    {
    }

    std::string     user_handle;

};

struct UserOnlineStatusEvent: public Event
{
    UserOnlineStatusEvent(
        const std::string   & user_handle,
        user_status_e       user_s,
        uint32_t            req_id):
            Event( req_id ),
            user_handle( user_handle ),
            status( user_s )
    {
    }

    std::string     user_handle;
    user_status_e   status;
};

struct CallEvent: public BasicCallEvent
{
    CallEvent(
        uint32_t            call_id,
        uint32_t            req_id ):
            BasicCallEvent( call_id, req_id )
    {
    }
};

struct CallDurationEvent: public BasicCallEvent
{
    CallDurationEvent(
        uint32_t            call_id,
        uint32_t            duration,
        uint32_t            req_id ):
            BasicCallEvent( call_id, req_id ),
            duration( duration )
    {
    }

    uint32_t            duration;
};

struct VoicemailDurationEvent: public BasicCallEvent
{
    VoicemailDurationEvent(
        uint32_t            call_id,
        uint32_t            duration,
        uint32_t            req_id ):
            BasicCallEvent( call_id, req_id ),
            duration( duration )
    {
    }

    uint32_t            duration;
};

struct CallStatusEvent: public BasicCallEvent
{
    CallStatusEvent(
        uint32_t            call_id,
        call_status_e       call_s,
        uint32_t            req_id ):
            BasicCallEvent( call_id, req_id ),
            status( call_s )
    {
    }

    call_status_e   status;
};

struct CallPstnStatusEvent: public BasicCallEvent
{
    CallPstnStatusEvent(
        uint32_t            call_id,
        uint32_t            error_code,
        const std::string   & descr,
        uint32_t            req_id ):
            BasicCallEvent( call_id, req_id ),
            error_code( error_code ),
            descr( descr )
    {
    }

    uint32_t            error_code;
    std::string         descr;
};

struct CallFailureReasonEvent: public BasicCallEvent
{
    CallFailureReasonEvent(
            uint32_t            call_id,
            uint32_t            reason,
            uint32_t            req_id ):
                BasicCallEvent( call_id, req_id ),
                reason( reason )
    {
    }

    uint32_t            reason;
};

struct CallVaaInputStatusEvent: public BasicCallEvent
{
    CallVaaInputStatusEvent(
            uint32_t            call_id,
            uint32_t            status,
            uint32_t            req_id ):
                BasicCallEvent( call_id, req_id ),
                status( status )
    {
    }

    uint32_t            status;
};

struct AlterCallSetInputFileEvent: public BasicCallEvent
{
    AlterCallSetInputFileEvent(
            uint32_t            call_id,
            const std::string   & filename,
            uint32_t            req_id ):
                BasicCallEvent( call_id, req_id ),
                filename( filename )
    {
    }

    std::string     filename;
};

struct AlterCallSetOutputFileEvent: public BasicCallEvent
{
    AlterCallSetOutputFileEvent(
            uint32_t            call_id,
            const std::string   & filename,
            uint32_t            req_id ):
                BasicCallEvent( call_id, req_id ),
                filename( filename )
    {
    }

    std::string     filename;
};

struct ChatEvent: public Event
{
    ChatEvent(
        uint32_t            req_id ):
            Event( req_id )
    {
    }
};

struct ChatMemberEvent: public Event
{
    ChatMemberEvent(
        uint32_t            req_id ):
            Event( req_id )
    {
    }
};

struct UserEvent: public Event
{
    UserEvent(
        uint32_t            req_id ):
            Event( req_id )
    {
    }
};


NAMESPACE_SKYPE_SERVICE_END

#endif  // SKYPE_SERVICE_EVENTS_H

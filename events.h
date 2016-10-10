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

// $Revision: 4784 $ $Date:: 2016-10-10 #$ $Author: serge $

#ifndef EVENTS_H
#define EVENTS_H

#include <string>                   // std::string

#include "parser_types.h"           // user_status_e, conn_status_e, call_status_e

#include "namespace_lib.h"          // NAMESPACE_SKYPE_SERVICE_START

NAMESPACE_SKYPE_SERVICE_START

struct Event
{
    Event( uint32_t            hash_id ):
        hash_id_( hash_id )
    {
    }

    virtual ~Event() {}

    uint32_t        hash_id_;
};

struct UnknownEvent: public Event
{
    UnknownEvent(
        const std::string   & descr,
        uint32_t            hash_id ):
            Event( hash_id ),
            descr_( descr )
    {
    }

    std::string         descr_;
};

struct BasicCallEvent: public Event
{
    BasicCallEvent(
        uint32_t            call_id,
        uint32_t            hash_id ):
            Event( hash_id ),
            call_id_( call_id )
    {
    }

    uint32_t          call_id_;
};

struct ErrorEvent: public Event
{
    ErrorEvent(
        uint32_t            error_code,
        const std::string   & descr,
        uint32_t            hash_id ):
            Event( hash_id ),
            error_code_( error_code ),
            descr_( descr )
    {
    }

    uint32_t            error_code_;
    std::string         descr_;
};

struct ConnStatusEvent: public Event
{
    ConnStatusEvent(
        conn_status_e       conn_s,
        uint32_t            hash_id ):
        Event( hash_id ),
        conn_s_( conn_s )
    {
    }

    conn_status_e   conn_s_;
};

struct UserStatusEvent: public Event
{
    UserStatusEvent(
        user_status_e       user_s,
        uint32_t            hash_id ):
        Event( hash_id ),
        user_s_( user_s )
    {
    }

    user_status_e   user_s_;
};

struct CurrentUserHandleEvent: public Event
{
    CurrentUserHandleEvent(
        const std::string   & user_handle,
        uint32_t            hash_id ):
            Event( hash_id ),
            user_handle_( user_handle )
    {
    }

    std::string     user_handle_;

};

struct UserOnlineStatusEvent: public Event
{
    UserOnlineStatusEvent(
        const std::string   & user_handle,
        user_status_e       user_s,
        uint32_t            hash_id):
            Event( hash_id ),
            user_handle_( user_handle ),
            user_s_( user_s )
    {
    }

    std::string     user_handle_;
    user_status_e   user_s_;
};

struct CallEvent: public BasicCallEvent
{
    CallEvent(
        uint32_t            call_id,
        uint32_t            hash_id ):
            BasicCallEvent( call_id, hash_id )
    {
    }
};

struct CallDurationEvent: public BasicCallEvent
{
    CallDurationEvent(
        uint32_t            call_id,
        uint32_t            duration,
        uint32_t            hash_id ):
            BasicCallEvent( call_id, hash_id ),
            duration_( duration )
    {
    }

    uint32_t            duration_;
};

struct VoicemailDurationEvent: public BasicCallEvent
{
    VoicemailDurationEvent(
        uint32_t            call_id,
        uint32_t            duration,
        uint32_t            hash_id ):
            BasicCallEvent( call_id, hash_id ),
            duration_( duration )
    {
    }

    uint32_t            duration_;
};

struct CallStatusEvent: public BasicCallEvent
{
    CallStatusEvent(
        uint32_t            call_id,
        call_status_e       call_s,
        uint32_t            hash_id ):
            BasicCallEvent( call_id, hash_id ),
            call_s_( call_s )
    {
    }

    call_status_e   call_s_;
};

struct CallPstnStatusEvent: public BasicCallEvent
{
    CallPstnStatusEvent(
        uint32_t            call_id,
        uint32_t            error_code,
        const std::string   & descr,
        uint32_t            hash_id ):
            BasicCallEvent( call_id, hash_id ),
            error_code_( error_code ),
            descr_( descr )
    {
    }

    uint32_t            error_code_;
    std::string         descr_;
};

struct CallFailureReasonEvent: public BasicCallEvent
{
    CallFailureReasonEvent(
            uint32_t            call_id,
            uint32_t            reason,
            uint32_t            hash_id ):
                BasicCallEvent( call_id, hash_id ),
                reason_( reason )
    {
    }

    uint32_t            reason_;
};

struct CallVaaInputStatusEvent: public BasicCallEvent
{
    CallVaaInputStatusEvent(
            uint32_t            call_id,
            uint32_t            status,
            uint32_t            hash_id ):
                BasicCallEvent( call_id, hash_id ),
                status_( status )
    {
    }

    uint32_t            status_;
};

struct AlterCallSetInputFileEvent: public BasicCallEvent
{
    AlterCallSetInputFileEvent(
            uint32_t            call_id,
            const std::string   & filename,
            uint32_t            hash_id ):
                BasicCallEvent( call_id, hash_id ),
                filename_( filename )
    {
    }

    std::string     filename_;
};

struct AlterCallSetOutputFileEvent: public BasicCallEvent
{
    AlterCallSetOutputFileEvent(
            uint32_t            call_id,
            const std::string   & filename,
            uint32_t            hash_id ):
                BasicCallEvent( call_id, hash_id ),
                filename_( filename )
    {
    }

    std::string     filename_;
};

struct ChatEvent: public Event
{
    ChatEvent(
        uint32_t            hash_id ):
            Event( hash_id )
    {
    }
};

struct ChatMemberEvent: public Event
{
    ChatMemberEvent(
        uint32_t            hash_id ):
            Event( hash_id )
    {
    }
};

struct UserEvent: public Event
{
    UserEvent(
        uint32_t            hash_id ):
            Event( hash_id )
    {
    }
};


NAMESPACE_SKYPE_SERVICE_END

#endif  // EVENTS_H

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

// $Revision: 3058 $ $Date:: 2015-12-24 #$ $Author: serge $

#ifndef EVENT_H
#define EVENT_H

#include <cstdint>                  // uint32_t

#include "namespace_lib.h"          // NAMESPACE_SKYPE_SERVICE_START

NAMESPACE_SKYPE_SERVICE_START

class Event
{
public:
    enum type_e
    {
        UNDEF = 0,
        UNKNOWN,
        ERROR,
        CONNSTATUS,
        USERSTATUS,
        CURRENTUSERHANDLE,
        USER_ONLINE_STATUS,
        CALL,
        CALL_DURATION,
        CALL_STATUS,
        CALL_PSTN_STATUS,
        CALL_FAILUREREASON,
        CHAT,
        CHATMEMBER,
        ALTER_CALL_SET_INPUT_SOUNDCARD,
        ALTER_CALL_SET_INPUT_PORT,
        ALTER_CALL_SET_INPUT_FILE,
        ALTER_CALL_SET_OUTPUT_SOUNDCARD,
        ALTER_CALL_SET_OUTPUT_PORT,
        ALTER_CALL_SET_OUTPUT_FILE,
        CALL_VAA_INPUT_STATUS,
        USER
    };

public:
    Event(
        Event::type_e       type,
        uint32_t            hash_id );

    virtual ~Event() {}

    type_e get_type() const;
    uint32_t get_hash_id() const;
    bool has_hash_id() const;

private:

    type_e          type_;
    uint32_t        hash_id_;
};

NAMESPACE_SKYPE_SERVICE_END

#endif  // EVENT_H

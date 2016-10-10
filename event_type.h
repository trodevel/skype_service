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

// $Revision: 4782 $ $Date:: 2016-10-10 #$ $Author: serge $

#ifndef EVENT_TYPE_H
#define EVENT_TYPE_H

#include <cstdint>                  // uint32_t

#include "namespace_lib.h"          // NAMESPACE_SKYPE_SERVICE_START

NAMESPACE_SKYPE_SERVICE_START

enum event_type_e
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
    VOICEMAIL_DURATION,
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

NAMESPACE_SKYPE_SERVICE_END

#endif  // EVENT_TYPE_H

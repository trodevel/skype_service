/*

Skype command generator.

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

#ifndef COMMAND_GEN_H
#define COMMAND_GEN_H

#include <string>                   // std::string

#include "namespace_lib.h"          // NAMESPACE_SKYPE_SERVICE_START
#include "parser_types.h"           // call_status_e

NAMESPACE_SKYPE_SERVICE_START

class CommandGen
{
public:
    static std::string protocol( uint32_t n, uint32_t req_id = 0 );
    static std::string call( const std::string & s, uint32_t req_id = 0 );
    static std::string get_call_property( uint32_t id, const std::string & s, uint32_t req_id = 0 );
    static std::string set_call_status( uint32_t id, call_status_e s, uint32_t req_id = 0 );
    static std::string alter_call_hangup( uint32_t id, uint32_t req_id = 0 );
    static std::string alter_call_set_input_soundcard( uint32_t id, uint32_t req_id = 0 );
    static std::string alter_call_set_input_port( uint32_t id, uint32_t p, uint32_t req_id = 0 );
    static std::string alter_call_set_input_file( uint32_t id, const std::string & s, uint32_t req_id = 0 );
    static std::string alter_call_set_output_soundcard( uint32_t id, uint32_t req_id = 0 );
    static std::string alter_call_set_output_port( uint32_t id, uint32_t p, uint32_t req_id = 0 );
    static std::string alter_call_set_output_file( uint32_t id, const std::string & s, uint32_t req_id = 0 );
    static std::string alter_call_set_capture_mic_port( uint32_t id, uint32_t p, uint32_t req_id = 0 );
    static std::string alter_call_set_capture_mic_file( uint32_t id, const std::string & s, uint32_t req_id = 0 );
};

NAMESPACE_SKYPE_SERVICE_END

#endif  // COMMAND_GEN_H

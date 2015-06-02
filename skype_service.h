/*

Skype Service.

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

// $Revision: 1804 $ $Date:: 2015-06-01 #$ $Author: serge $

#ifndef SKYPE_SERVICE_H
#define SKYPE_SERVICE_H

#include <string>                   // std::string
#include <mutex>                    // std::mutex

#include "../threcon/i_controllable.h"  // IControllable
#include "../utils/types.h"             // uint32
#include "../skype_io/skype_low_io.h"   // SkypeLowIo

#include "namespace_lib.h"          // NAMESPACE_SKYPE_SERVICE_START
#include "event_gen.h"              // EventGen
#include "parser_types.h"           // call_status_e

NAMESPACE_SKYPE_SERVICE_START

class SkypeService: public virtual threcon::IControllable
{

public:
    SkypeService();
    ~SkypeService();

    bool init();

    // interface threcon::IControllable
    bool shutdown();

    bool is_inited() const;

    bool register_callback( ICallback * eh );

    bool send_raw( const std::string & s );

    // Skype interface
    bool call( const std::string & s, uint32 hash_id = 0 );
    bool get_call_property( uint32 id, const std::string & s, uint32 hash_id = 0 );
    bool set_call_status( uint32 id, call_status_e s, uint32 hash_id = 0 );
    bool alter_call_hangup( uint32 id, uint32 hash_id = 0 );
    bool alter_call_set_input_soundcard( uint32 id, uint32 hash_id = 0 );
    bool alter_call_set_input_port( uint32 id, uint32 p, uint32 hash_id = 0 );
    bool alter_call_set_input_file( uint32 id, const std::string & s, uint32 hash_id = 0 );
    bool alter_call_set_output_soundcard( uint32 id, uint32 hash_id = 0 );
    bool alter_call_set_output_port( uint32 id, uint32 p, uint32 hash_id = 0 );
    bool alter_call_set_output_file( uint32 id, const std::string & s, uint32 hash_id = 0 );
    bool alter_call_set_capture_mic_port( uint32 id, uint32 p, uint32 hash_id = 0 );
    bool alter_call_set_capture_mic_file( uint32 id, const std::string & s, uint32 hash_id = 0 );

    std::string get_error_msg() const;

private:

private:

    mutable std::mutex      mutex_;

    skype_io::SkypeLowIo    sio_;

    EventGen                event_gen_;
};

NAMESPACE_SKYPE_SERVICE_END

#endif  // SKYPE_SERVICE_H

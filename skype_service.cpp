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

// $Revision: 3417 $ $Date:: 2016-02-16 #$ $Author: serge $

#include "skype_service.h"          // self

#include "../utils/mutex_helper.h"  // MUTEX_SCOPE_LOCK
#include "../utils/dummy_logger.h"  // dummy_log
#include "command_gen.h"            // CommandGen

#define MODULENAME      "SkypeService"


NAMESPACE_SKYPE_SERVICE_START

SkypeService::SkypeService()
{
}

SkypeService::~SkypeService()
{
    dummy_log_debug( MODULENAME, "~SkypeService()" );

    MUTEX_SCOPE_LOCK( mutex_ );
}

bool SkypeService::init()
{
    dummy_log_debug( MODULENAME, "init()" );

    MUTEX_SCOPE_LOCK( mutex_ );

    if( sio_.is_inited() )
    {
        dummy_log_error( MODULENAME, "init: already inited" );
        return false;
    }

    bool b = sio_.init();

    if( b == false )
    {
        return false;
    }

    return sio_.register_callback( &event_gen_ );
}

bool SkypeService::is_inited() const
{
    MUTEX_SCOPE_LOCK( mutex_ );

    return sio_.is_inited();
}

bool SkypeService::send_raw( const std::string & s )
{
    MUTEX_SCOPE_LOCK( mutex_ );

    return sio_.send( s );
}

std::string SkypeService::get_error_msg() const
{
    MUTEX_SCOPE_LOCK( mutex_ );

    return sio_.get_error_msg();
}

bool SkypeService::shutdown()
{
    dummy_log_debug( MODULENAME, "shutdown()" );

    MUTEX_SCOPE_LOCK( mutex_ );

    return sio_.shutdown();
}

bool SkypeService::register_callback( ICallback * eh )
{
    MUTEX_SCOPE_LOCK( mutex_ );

    return event_gen_.register_callback( eh );
}

// Skype interface
bool SkypeService::call( const std::string & s, uint32_t hash_id )
{
    std::string cmd = CommandGen::call( s, hash_id );

    MUTEX_SCOPE_LOCK( mutex_ );

    return sio_.send( cmd );
}
bool SkypeService::get_call_property( uint32_t id, const std::string & s, uint32_t hash_id )
{
    std::string cmd = CommandGen::get_call_property( id, s, hash_id );

    MUTEX_SCOPE_LOCK( mutex_ );

    return sio_.send( cmd );
}
bool SkypeService::set_call_status( uint32_t id, call_status_e s, uint32_t hash_id )
{
    std::string cmd = CommandGen::set_call_status( id, s, hash_id );

    MUTEX_SCOPE_LOCK( mutex_ );

    return sio_.send( cmd );
}
bool SkypeService::alter_call_hangup( uint32_t id, uint32_t hash_id )
{
    std::string cmd = CommandGen::alter_call_hangup( id, hash_id );

    MUTEX_SCOPE_LOCK( mutex_ );

    return sio_.send( cmd );
}
bool SkypeService::alter_call_set_input_soundcard( uint32_t id, uint32_t hash_id )
{
    std::string cmd = CommandGen::alter_call_set_input_soundcard( id, hash_id );

    MUTEX_SCOPE_LOCK( mutex_ );

    return sio_.send( cmd );
}
bool SkypeService::alter_call_set_input_port( uint32_t id, uint32_t p, uint32_t hash_id )
{
    std::string cmd = CommandGen::alter_call_set_input_port( id, p, hash_id );

    MUTEX_SCOPE_LOCK( mutex_ );

    return sio_.send( cmd );
}
bool SkypeService::alter_call_set_input_file( uint32_t id, const std::string & s, uint32_t hash_id )
{
    std::string cmd = CommandGen::alter_call_set_input_file( id, s, hash_id );

    MUTEX_SCOPE_LOCK( mutex_ );

    return sio_.send( cmd );
}
bool SkypeService::alter_call_set_output_soundcard( uint32_t id, uint32_t hash_id )
{
    std::string cmd = CommandGen::alter_call_set_output_soundcard( id, hash_id );

    MUTEX_SCOPE_LOCK( mutex_ );

    return sio_.send( cmd );
}
bool SkypeService::alter_call_set_output_port( uint32_t id, uint32_t p, uint32_t hash_id )
{
    std::string cmd = CommandGen::alter_call_set_output_port( id, p, hash_id );

    MUTEX_SCOPE_LOCK( mutex_ );

    return sio_.send( cmd );
}
bool SkypeService::alter_call_set_output_file( uint32_t id, const std::string & s, uint32_t hash_id )
{
    std::string cmd = CommandGen::alter_call_set_output_file( id, s, hash_id );

    MUTEX_SCOPE_LOCK( mutex_ );

    return sio_.send( cmd );
}
bool SkypeService::alter_call_set_capture_mic_port( uint32_t id, uint32_t p, uint32_t hash_id )
{
    std::string cmd = CommandGen::alter_call_set_capture_mic_port( id, p, hash_id );

    MUTEX_SCOPE_LOCK( mutex_ );

    return sio_.send( cmd );
}
bool SkypeService::alter_call_set_capture_mic_file( uint32_t id, const std::string & s, uint32_t hash_id )
{
    std::string cmd = CommandGen::alter_call_set_capture_mic_file( id, s, hash_id );

    MUTEX_SCOPE_LOCK( mutex_ );

    return sio_.send( cmd );
}


NAMESPACE_SKYPE_SERVICE_END

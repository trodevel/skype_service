/*

Dummy event handler.

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

// $Revision: 1801 $ $Date:: 2015-06-01 #$ $Author: serge $

#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <string>                   // std::string

#include "namespace_lib.h"          // NAMESPACE_SKYPE_SERVICE_START
#include "i_callback.h"             // ICallback

NAMESPACE_SKYPE_SERVICE_START

class EventHandler: public ICallback
{

public:
    virtual void on_conn_status( const conn_status_e s )    {};
    virtual void on_user_status( const user_status_e s )    {};
    virtual void on_current_user_handle( const std::string & s )    {};
    virtual void on_user_online_status( const std::string & u, const user_status_e s )    {};
    virtual void on_unknown( const std::string & g )                            {};

    virtual void on_call_status( const uint32 n, const call_status_e s )        {};
    virtual void on_call_duration( const uint32 n, const uint32 t )             {};
    virtual void on_call_failure_reason( const uint32 n, const uint32 c )       {};
};

NAMESPACE_SKYPE_SERVICE_END

#endif  // EVENT_HANDLER_H

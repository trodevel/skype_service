/*

Event generator.

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

#ifndef EVENT_GEN_H
#define EVENT_GEN_H

#include <mutex>                    // std::mutex

#include "../skype_io/i_callback.h" // ICallback
#include "i_callback.h"             // ICallback

NAMESPACE_SKYPE_SERVICE_START

class EventGen: public skype_io::ICallback
{
public:
    EventGen();

    virtual void handle( const std::string & s );

    bool register_callback( skype_service::ICallback * callback );

private:
    mutable std::mutex          mutex_;

    skype_service::ICallback    * callback_;
};

NAMESPACE_SKYPE_SERVICE_END

#endif  // EVENT_GEN_H

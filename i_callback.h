/*

Event handler interface.

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

#ifndef I_SKYPE_SERVICE_CALLBACK_H
#define I_SKYPE_SERVICE_CALLBACK_H

#include "namespace_lib.h"          // NAMESPACE_SKYPE_SERVICE_START

NAMESPACE_SKYPE_SERVICE_START

class Event;

class ICallback
{
public:
    virtual ~ICallback() {};

    virtual void consume( const Event * e )     = 0;
};

NAMESPACE_SKYPE_SERVICE_END

#endif  // I_SKYPE_SERVICE_CALLBACK_H

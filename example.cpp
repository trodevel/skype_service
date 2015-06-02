/*

SkypeService usage example.

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

#include <thread>           // std::thread
#include <functional>       // std::bind
#include <iostream>         // cout

#include "../utils/dummy_logger.h"      // dummy_log_set_log_level
#include "skype_service.h"  // SkypeService
#include "event.h"          // Event

class Callback: virtual public skype_service::ICallback
{
public:
    Callback( skype_service::SkypeService * serv ):
        serv_( serv )
    {
    }

    // callback interface
    virtual void consume( const skype_service::Event * e )
    {
        std::cout << "got event " << e->get_type();

        if( e->has_hash_id() )
            std::cout << " #" << e->get_hash_id();

        std::cout << std::endl;

        delete e;
    }

    void control_thread()
    {
        std::cout << "type exit or quit to quit: " << std::endl;

        std::string input;

        while( true )
        {
            std::cout << "your command: ";

            std::getline( std::cin, input );

            std::cout << "command: " << input << std::endl;

            if( input == "exit" || input == "quit" )
                break;

            bool b = serv_->send_raw( input );

            if( b == false )
            {
                std::cout << "ERROR: cannot process command '" << input << "'" << std::endl;
            }

        };

        std::cout << "exiting ..." << std::endl;

        serv_->shutdown();
    }

private:
    skype_service::SkypeService * serv_;
};


int main( int argc, char **argv )
{
    dummy_logger::set_log_level( log_levels_log4j::TRACE );

    skype_service::SkypeService serv;

    bool b = serv.init();

    if( !b )
    {
        std::cout << "cannot initialize SkypeService - " << serv.get_error_msg() << std::endl;
        return 0;
    }

    Callback test( &serv );

    serv.register_callback( &test );

    std::thread t( std::bind( &Callback::control_thread, &test ) );

    t.join();

    std::cout << "Done! =)" << std::endl;

    return 0;
}

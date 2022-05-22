
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <ion.h>
#include <ion/timing.h>
#include <ion/events.h>

#include "display.h"

#include "sys_llapi.h"

void Ion::Timing::msleep(uint32_t ms)
{
    //ll_vmsleep_ms(ms);
    
    uint32_t start_time = ll_gettime_us() / 1000;
    while((ll_gettime_us() / 1000) - start_time < ms)
    {
        ;
    }
}

uint64_t Ion::Timing::millis()
{
    return ll_gettime_us()/1000;
    //return ll_gettime_us();
}

extern "C"
{

    int cpp_main(int argc, char *argv[])
    {
        Ion::Simulator::Main::init();

        /*
        std::vector<const char *> arguments(argv, argv + argc);
        const char *language = "en";
        if (language != nullptr)
        {
            arguments.push_back("--language");
            arguments.push_back(language);
        }*/

        //uint32_t *test;
        //test = (uint32_t *)malloc(1024);
        //free(test);
        ll_putStr("ion_main.\n");
        
        //ion_main(arguments.size(), &arguments[0]);
        ion_main(0, nullptr);
    }
}

namespace Ion
{
    namespace Simulator
    {
        namespace Main
        {

            static bool sNeedsRefresh = false;

            void init()
            {
                Display::init();
            }

            void quit()
            {
            }

            void setNeedsRefresh()
            {
                sNeedsRefresh = true;
            }

            void refresh()
            {
                if(!sNeedsRefresh)
                {
                    return;
                }

                Display::draw();
                
                //ll_putStr("refresh\n");

                sNeedsRefresh = false;
            }
            void relayout()
            {
                //Display::draw();
                setNeedsRefresh();
            }

        }
    }
}

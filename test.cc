#include "dramsim3_wrapper.h"
#include <iostream>
int main()
{
    auto dram = get_dramsim3();
    for (int i = 0; i < 10; i++)
    {
        dramsim3_send(dram, i * 64, false);
        dramsim3_tick(dram);
    }
    for (int i = 0; i < 10; i++)
    {
        while (!dramsim3_ret_available(dram))
        {
            dramsim3_tick(dram);
        }
        auto ret = dramsim3_get(dram);
        std::cout << ret << std::endl;
    }
}
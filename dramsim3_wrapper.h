#include<queue>
#include "dramsim3.h"

extern "C"
{
   

    int dramsim3_get_channel_id(void *,unsigned long long addr);
    void *get_dramsim3();
    bool dramsim3_send(void *dramsim3, unsigned long long addr, bool is_write);
    unsigned long long dramsim3_get(void *dramsim3);
    void dramsim3_tick(void *dramsim3);
    bool dramsim3_ret_available(void *);
    bool dramsim3_available(void *,unsigned long long addr, bool is_write);
    void delete_dramsim3(void *);
}

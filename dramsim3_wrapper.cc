#include "dramsim3_wrapper.h"
#include <iostream>
#include "queue"
#include "dramsim3.h"
struct dramsim_wrapper
{
    std::queue<unsigned long long> *return_queue = 0;
    dramsim3::MemorySystem *m_dramsim = 0;
};

int dramsim3_get_channel_id(void *dramsim3_wrapper, uint64_t addr)
{
    auto m_wrapper = (dramsim_wrapper *)dramsim3_wrapper;

    return m_wrapper->m_dramsim->GetChannel(addr);
}

void *get_dramsim3()
{
    dramsim_wrapper *m_wrapper = new dramsim_wrapper;
    m_wrapper->m_dramsim = dramsim3::GetMemorySystem(
        "/Users/jiangqiushen/git/gcn_rust/dramsim3-wrapper/DRAMsim3/configs/HBM2_8Gb_x128.ini", ".",
        [=](uint64_t addr) {
            m_wrapper->return_queue->push(addr);
        },
        [](uint64_t addr) {});
    m_wrapper->return_queue = new std::queue<unsigned long long>;
    return m_wrapper;
}

void delete_dramsim3(void *dramsim3_wrapper)
{
    auto m_wrapper = (dramsim_wrapper *)dramsim3_wrapper;

    delete m_wrapper->m_dramsim;
    delete m_wrapper->return_queue;
    std::cout << "deleted!!" << std::endl;
    delete m_wrapper;
}

bool dramsim3_send(void *dramsim3_wrapper, unsigned long long addr, bool is_write)
{
    auto m_wrapper = (dramsim_wrapper *)dramsim3_wrapper;
    auto result = m_wrapper->m_dramsim->AddTransaction(addr, is_write);
    return result;
}

unsigned long long dramsim3_get(void *dramsim3_wrapper)
{
    auto m_wrapper = (dramsim_wrapper *)dramsim3_wrapper;

    if (m_wrapper->return_queue->size())
    {
        auto result = m_wrapper->return_queue->front();
        m_wrapper->return_queue->pop();
        return result;
    }
    else
    {
        return -1;
    }
}

void dramsim3_tick(void *dramsim3_wrapper)
{
    auto m_wrapper = (dramsim_wrapper *)dramsim3_wrapper;

    m_wrapper->m_dramsim->ClockTick();
}

bool dramsim3_ret_available(void *dramsim3_wrapper)
{
    auto m_wrapper = (dramsim_wrapper *)dramsim3_wrapper;
    return m_wrapper->return_queue->size();
}

bool dramsim3_available(void *dramsim3_wrapper, unsigned long long addr, bool is_write)
{
    auto m_wrapper = (dramsim_wrapper *)dramsim3_wrapper;
    return m_wrapper->m_dramsim->WillAcceptTransaction(addr, is_write);
}
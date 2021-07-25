#include "memory.h"

arr2d Memory_tmp; // 8GB physical memory

int
init_memory()
{
    Memory_tmp = new unsigned char[NUM_PHYSICAL_MEM_FRAMES][FRAME_SIZE];
    if (!Memory_tmp)
        return -1;
    return 0;
}

void
exit_memory()
{
    delete Memory_tmp;
}
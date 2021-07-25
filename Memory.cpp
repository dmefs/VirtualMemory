#include "memory.h"

int
init_memory()
{
    Memory = new unsigned char[NUM_PHYSICAL_MEM_FRAMES][FRAME_SIZE];
    if (!Memory)
        return -1;
    return 0;
}

void
exit_memory()
{
    delete Memory;
}
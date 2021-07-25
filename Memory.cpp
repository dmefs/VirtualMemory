#include "memory.h"
#include <iostream>

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

Memory::Memory()
  : start_line(0)
  , gap_line(0)
  , write_count(0)
{
    array = new unsigned char[PHY_ADDRESS_SPACE_BITS];
    if (!array) {
        std::cerr << "Failed to create class Memory.\n";
        exit(-1);
    }
}
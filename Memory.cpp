#include "memory.h"
#include "Byte.h"
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

long Memory::num_line_ex_gap = NUM_LINES - 1;
long Memory::trigger_times = 100;

Memory::Memory()
  : start_line(0)
  , gap_line(NUM_LINES - 1)
  , write_count(0)
{
    array = new Byte[PHY_ADDRESS_SPACE_SIZE];
    if (!array) {
        std::cerr << "Failed to create class Memory.\n";
        exit(-1);
    }
}
Memory::~Memory()
{
    delete[] array;
}
/*
    Gap Movement.
*/
void
Memory::update_gap()
{
    if (gap_line == 0) {
        start_line = (start_line + 1) % num_line_ex_gap;
        copy_line(num_line_ex_gap, gap_line);
        gap_line = num_line_ex_gap;
    } else {
        copy_line(gap_line - 1, gap_line);
        gap_line -= 1;
    }
}

/*
    Mapping of Logical Address to Physical Address.
*/
long
Memory::la_to_pa(long fnum, long offset)
{
    unsigned long logical_address = ((unsigned long)fnum << FRAME_SIZE_BITS) + offset;
    long log_line_num = (long)(logical_address >> LINE_SIZE_BITS);
    long phy_line_num = (log_line_num + start_line) % num_line_ex_gap;
    phy_line_num = (phy_line_num >= gap_line) ? phy_line_num + 1 : phy_line_num;
    long phy_address = (long)((unsigned long)phy_line_num << LINE_SIZE_BITS) + offset;
    return phy_address;
}

/*
    Update Memory info 
*/
bool
Memory::write(long fnum, long offset)
{
    if (fnum < 0) {
        std::cerr << "Error: fnum < 0 in " << __func__ << std::endl;
        return false;
    }
    if (offset < 0) {
        std::cerr << "Error: offset < 0 in " << __func__ << std::endl;
        return false;
    }
    long phy_address = la_to_pa(fnum, offset);
    array[phy_address].write();

    write_count++;
    if (write_count >= trigger_times) {
        update_gap();
        write_count = 0;
    }
    return true;
}

bool
Memory::copy_line(long from_line_num, long to_line_num)
{
    // no need to read now
    unsigned long to = ((unsigned long)to_line_num << LINE_SIZE_BITS);
    for (unsigned long i = 0; i < (unsigned long)LINE_SIZE; i++) {
        array[to + i].write();
    }
    return true;
}

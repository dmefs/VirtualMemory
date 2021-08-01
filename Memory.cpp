#include "Memory.h"
#include <iostream>
#include "FeistelNetwork.h"
#include "Line.h"

unsigned long Memory::num_line_ex_gap = NUM_LINES - 1;
long Memory::trigger_times = 100;

Memory::Memory() : start_line(0), gap_line(NUM_LINES - 1), write_count(0)
{
    array = new Line[NUM_LINES];
    if (!array) {
        std::cerr << "Failed to create class Memory.\n";
        exit(-1);
    }
    FeistelNetwork::init();
}

Memory::~Memory()
{
    delete[] array;
}
/*
    Gap Movement.
*/
void Memory::update_gap()
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

unsigned long Memory::ia_to_pa(unsigned long inter_line_num)
{
    unsigned long phy_line_num =
        (inter_line_num + start_line) % num_line_ex_gap;
    unsigned long result =
        (phy_line_num >= gap_line) ? phy_line_num + 1 : phy_line_num;
    return result;
}

unsigned long Memory::la_to_ia(unsigned long log_line_num)
{
    return FeistelNetwork::cal(log_line_num);
}

/*
    Mapping of Logical Address to Physical Address.
*/
unsigned long Memory::la_to_pa(unsigned long log_line_num)
{
    unsigned long ia = la_to_ia(log_line_num);
    unsigned long pa = ia_to_pa(ia);
    return pa;
}

/*
    Update Memory info
*/
bool Memory::write(long log_addr)
{
    if (log_addr < 0) {
        std::cerr << "Error: log_addr < 0 in " << __func__ << std::endl;
        return false;
    }
    unsigned long log_lnum = ((unsigned long) log_addr >> LINE_SIZE_BITS);
    long phy_lnum = la_to_pa(log_lnum);
    array[phy_lnum].write();
    std::cout << "Line: " << phy_lnum << std::endl;

    write_count++;
    if (write_count >= trigger_times) {
        update_gap();
        write_count = 0;
    }
    return true;
}

bool Memory::copy_line(unsigned long from_line_num, unsigned long to_line_num)
{
    // no need to read now
    array[to_line_num].write();
    return true;
}

#pragma once
/*
Define the page (frame) size, logical and physical memory size; declare
the Memory_tmp array (but not define it).
*/

const long PHY_ADDRESS_SPACE_BITS = 20;
const long FRAME_SIZE_BITS = 12; // lower 12 bits of logical memory address

const long
  NUM_LOGICAL_MEM_FRAMES =        // logical memory has 48 bits virtual address
                                  // frames/pages (each logical address
  (1L << PHY_ADDRESS_SPACE_BITS); // has 16 bits)

const long NUM_PHYSICAL_MEM_FRAMES = (1L << (PHY_ADDRESS_SPACE_BITS - FRAME_SIZE_BITS)); // physical memory has 4GB
const long FRAME_SIZE =
  (1 << FRAME_SIZE_BITS); // 2^FRAME_SIZE_BITS, Default is 4k, same as page
                          // size (in number of bytes)
const long FRAME_OFFSET_MASK =
  FRAME_SIZE - 1; // mask to preserve the lower 12 bits
const int TLB_NUM =
  64; // max number of entries in the translation lookaside buffer

const long LINE_SIZE_BITS = 8;
const long LINE_SIZE = 1L << LINE_SIZE_BITS;
const long NUM_LINES = 1L << (PHY_ADDRESS_SPACE_BITS - LINE_SIZE_BITS);

using arr2d = unsigned char (*)[FRAME_SIZE];
extern arr2d Memory_tmp; // 8GB physical memory
int
init_memory();

void
exit_memory();

class Memory
{
  public:
    Memory();
    bool write(long fnum, long offset);

  private:
    unsigned char* array;
    long start_line, gap_line;
    long write_count;
};

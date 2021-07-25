#pragma once
/*
Define the page (frame) size, logical and physical memory size; declare
the Memory array (but not define it).
*/

const long ADDRESS_SPACE = 12;
const long FRAME_SIZE_BITS = 8; // lower 12 bits of logical memory address

const long
    NUM_LOGICAL_MEM_FRAMES = // logical memory has 48 bits virtual address
                             // frames/pages (each logical address
    (1L << ADDRESS_SPACE);   // has 16 bits)

const long NUM_PHYSICAL_MEM_FRAMES = (1L << (ADDRESS_SPACE - FRAME_SIZE_BITS)); // physical memory has 4GB
const long FRAME_SIZE =
    (1 << FRAME_SIZE_BITS); // 2^FRAME_SIZE_BITS, Default is 4k, same as page
                            // size (in number of bytes)
const long FRAME_OFFSET_MASK =
    FRAME_SIZE - 1; // mask to preserve the lower 12 bits
const int TLB_SIZE =
    64; // max number of entries in the translation lookaside buffer

using arr2d = unsigned char (*)[FRAME_SIZE];
extern arr2d Memory; // 8GB physical memory
int init_memory();

void exit_memory();
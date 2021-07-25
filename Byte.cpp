#include "Byte.h"

Byte::Byte()
  : count(0)
{
}

void
Byte::write()
{
    count += 1;
}
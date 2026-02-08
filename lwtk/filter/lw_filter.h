#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define LW_FILTER_MEMCPY(dst, src, size) memcpy(dst, src, size)
#define LW_FILTER_MEMSET(buf, value, size) memset(buf, value, size)
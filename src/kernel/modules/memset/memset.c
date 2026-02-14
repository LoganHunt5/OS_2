#include "memset.h"

void *memset(void *dest, u8 val, u32 n){
  u8 *data_pointer = (u8*) dest;
  for(size_t i = 0; i < n; i++){
    data_pointer[i] = val;
  }
  return dest;
}


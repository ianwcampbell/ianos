#include <kernel/atag.h>

uint64_t get_mem_size(atag_t * tag) {
   while (tag->tag != NONE) {
       if (tag->tag == MEM) {
           return tag->mem.size;
       }
       tag = (atag_t *)(((uint64_t *)tag) + tag->tag_size);
   }
   return (1024*1024*512);

}

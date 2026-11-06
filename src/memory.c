/** @file memory.c
 *  @brief Implements starting point for a memory hierarchy with caching and
 * RAM.
 *  @see memory.h
 */

#include "memory.h"
#include "config.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static unsigned long instr_count;

// Structures for cache, element and memory hierarchy
typedef struct cache_element element_t;
typedef struct cache_structure cache_t;
typedef struct cache_active_memory memory_t;

static memory_t *memory_hierarchy;

// Define structs
struct cache_element {
  int valid_bit;
  int tag_bit;
  int index_bit; // do not need
  int offset; // do not need
  
  int dirty_bit;
  data_t data;
};

struct cache_structure {
  element_t *Cache_Lines;
  int cache_size;
  int associativity;
  int line_size;
  replace_t replace;
  write_t write;

  // For.calcultaion
  int lines;
  int sets;
  int offset;
  int index;
  int tag;

  // hit / miss
  int r_hit;
  int r_miss;

  int w_hit;
  int w_miss;
};

struct cache_active_memory {
  cache_t *L1i;
  cache_t *L1d;
  cache_t *L2;
};

/** Function creates a single cache level based on the given parametres defined in the config.h file.
 */
cache_t *new_cache(int cache_size,int line_size, int cache_associativity, replace_t replacement_policy, write_t write_policy) {
  cache_t *cache = malloc(sizeof(cache_t));
  if (cache == NULL) {
    printf("Memory allocation of cache failed\n");
    return NULL;
  }
  cache->cache_size = cache_size;
  cache->line_size = line_size;
  cache->associativity = cache_associativity;
  cache->replace = replacement_policy;
  cache->write = write_policy;
  
  cache->Cache_Lines = calloc(1024, cache_size);
  cache->lines = (cache_size * 1024) / line_size;
  cache->sets = cache->lines / cache_associativity;
  cache->offset = log2(line_size);
  cache->index = log2(cache->sets);
  cache->tag = line_size - cache->offset - cache->index;
  if (cache->tag + cache->offset + cache->index != cache->line_size) {
    printf("Stuff is wrong in the calculation");
    return NULL;
  }

  cache->r_hit = 0;
  cache->w_hit = 0;
  cache->r_miss = 0;
  cache->w_miss = 0;

  return cache;
}

/** new_element() creates a new adress-data element that can be added to a given cache.
 */
element_t *new_element(uint32_t address, data_t data, int tag_size, int index_size, int offset_size) {
  element_t *element = malloc(sizeof(element_t));
  if (element == NULL) {
    printf("Memory allocation of new element failed \n");
    return NULL;
  }
  element->data = data;
  element->valid_bit = 1;
  element->index_bit = address >> offset_size;
  element->offset = address & 0x3F;
  element->tag_bit = address >> 13;

  return element;
};

/** dissect_address takes an array and converts the given address into the tag-bit(0), index-bit(1) and tag-bit(2).
If a parameter isn't relevant, write 0 for it.
 */
void dissect_address(uint32_t instruction_adress, double data_address, int offset_size, int tag_size, int index_size, int tag, int offset, int index, int results[3]) {
  if (instruction_adress) {
    uint32_t address = instruction_adress;
  }
  else {
    uint64_t address = data_address;
  }
  if (tag) {
    results[0] = address >> (index_size + offset_size);
  }
  if (index) {
    results[1] = (address >> offset_size) & 0x7F;
  }
  if (offset) {
    results[2] = address & 0x3F;
  }
}

/** destroy_cache frees all elements in the cache and the cache itself. */
void destroy_cache(cache_t *cache){
  element_t *array = cache->Cache_Lines;
  for (int i = 0; i < cache->lines; i++) {
    element_t element_to_destory = array[i];
    free(element_to_destory);
  }
  free(cache);
  return;
};


void memory_init(void)
{
  instr_count = 0;
  // Create the memory structure
  memory_hierarchy = malloc(sizeof(memory_t));
  if (memory_hierarchy == NULL) {
    printf("Allocation of memory failed\n");
  }

  // Create Caches and connect to memory structure
  memory_hierarchy->L1d = new_cache(L1I_CACHE_SIZE, L1I_LINE_SIZE, L1I_ASSOCIATIVITY, L1I_REPLACEMENT, L1I_WRITE);
  memory_hierarchy->L1i = new_cache(L1D_CACHE_SIZE, L1D_LINE_SIZE, L1D_ASSOCIATIVITY, L1D_REPLACEMENT, L1D_WRITE);
  memory_hierarchy->L2 = new_cache(L2_CACHE_SIZE, L2_LINE_SIZE, L2_ASSOCIATIVITY, L2_REPLACEMENT, L2_WRITE);

}

void memory_fetch(uint32_t* address, data_t *data)
{
  printf("memory: fetch %p\n", address);
  if (data)
    *data = (data_t)0;

  instr_count++;

  // ------------------------------------- //

  // Get index from adress
  // Check in L1d cache
    // Note hit or miss, and return or continue
  // IF miss check in L2 cache
    // Note hit or miss, and return or continue
  // IF miss
    // Create new cache element
    // Write to L1d AND L2

}

void memory_read(double* address, data_t *data)
{
  printf("memory: read %p\n", address);
  if (data)
    *data = (data_t)0;

  instr_count++;

  // ------------------------------------- //

  // Get index from adress
  // Check in L1i cache
    // Note hit or miss, and return or continue
  // IF miss check in L2 cache
    // Note hit or miss, and return or continue
  // IF miss
    // Create new cache element
    // Get index
      // Check in L1i in set
        // Based on Replacement policy
        // Check valid bit and replace
        // Select random spot and replace
      // Check in L1i
    // Write to L1d AND L2

  // !!!! Need to hadd replacement check and
}

void memory_write(double* address, data_t *data)
{
  printf("memory: write %p\n", address);

  instr_count++;

  // ------------------------------------- //

  // Get index from adress
  // Check L1d for element
    // Evaluate write hit/miss and continue
  // Based on replacement policy
  // Check L2 for element
    // Evaluate write hit/miss and continue
  // Based on replacement policy 
}

void memory_finish(void)
{
  fprintf(stdout, "Executed %lu instructions.\n\n", instr_count);

  /* Deinitialize memory subsystem here */

  // ------------------------------------- //

  // Call destroy_cache on each cache level
  // Call free on the chaches in the memory hierarchy
  // Call fre on the memory hierarchy  

  // Print "Destruction order completed." or smt like that
}

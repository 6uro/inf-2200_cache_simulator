/** @file memory.c
 *  @brief Implements starting point for a memory hierarchy with caching and
 * RAM.
 *  @see memory.h
 */

#include "memory.h"
#include "config.h"   // configuration file for cache specifications

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

static unsigned long instr_count;

typedef struct cache_element {
  uint32_t tag;
  uint32_t valid;
  uint32_t dirty;
  uint32_t age;
}element_t;

typedef struct hit_miss_results {
  uint32_t read_hit;
  uint32_t read_miss;
  uint32_t write_hit;
  uint32_t write_miss;
  uint32_t read_hit_ratio;
  uint32_t read_miss_ratio;
  uint32_t write_miss_ratio;
  uint32_t write_hit_ratio;
}results_t;

typedef struct cache_struct {
  element_t *cache_lines;
  results_t results;
  uint32_t total_lines;
  uint32_t total_sets;
  uint32_t associativity;
  write_t write_policy;
  replace_t replace_policy;

  uint32_t index_size;
  uint32_t offset_size;
  uint32_t tag_size;
}cache_t;

static cache_t *L1i;
static cache_t *L1d;
static cache_t *L2;

/** Initialize cachees
 */
cache_t *create_cache(int cache_size,int line_size, int cache_associativity, replace_t replacement_policy, write_t write_policy){
  cache_t *cache = malloc(sizeof(cache_t));
  if (cache == NULL) {
    printf("Allocation of cache memory failed\n");
    return NULL;
  }

  // Allocate number of sets with number of elements, with total number of sets
  cache->cache_lines = calloc(cache->total_sets, cache_associativity * sizeof(element_t));
  if (cache->cache_lines == NULL) {
    printf("Memory allocation for cache failed, returning\n");
    return NULL;
  }

  cache->associativity = cache_associativity;
  cache->total_lines = (cache_size * 1028) / line_size;
  cache->total_sets = cache->total_lines  / cache_associativity;

  cache->results.read_hit = 0;
  cache->results.read_miss = 0;
  cache->results.write_hit = 0;
  cache->results.write_miss = 0;
  
  // Calculate bit-sizes
  cache->index_size = log2(cache->total_sets);
  cache->offset_size = log2(line_size);
  cache->tag_size = line_size - cache->index_size - cache->offset_size;

  // Calculate bit-mask (?)


  return cache;
};

typedef struct index_tag_bit {
  uint32_t index_instr;
  uint32_t tag_instr;
  uint64_t index_data;
  uint64_t tag_data;
}bits_t;

/** retrieve wanted bit from address
*/
bits_t get_address_bits(cache_t *cache, uint32_t instruction_address, double data_address){
  // Chech how to transfere adress properly so we can operate on it. Right now it's wrong.
  bits_t index_tag;

  if (instruction_address) {
    index_tag.index_instr = (instruction_address >> cache->offset_size) & 0x7F;
    index_tag.tag_instr = instruction_address >> (cache->offset_size + cache->index_size);
    return index_tag;
  }
  else if (data_address) {
    index_tag.index_data = ((uint64_t)data_address >> cache->offset_size) & 0x7F;
    index_tag.tag_data = (uint64_t)data_address >> (cache->offset_size + cache->index_size);
    return index_tag;
  }
  
  printf("Inputs not matching requisitions, retunrning\n");
  return index_tag;
};


void memory_init(void)
{
  /* Initialize memory subsystem here. */
  L1d = create_cache(L1I_CACHE_SIZE, L1I_LINE_SIZE, L1I_ASSOCIATIVITY, L1I_REPLACEMENT, L1I_WRITE);
  L1i = create_cache(L1D_CACHE_SIZE, L1D_LINE_SIZE, L1D_ASSOCIATIVITY, L1D_REPLACEMENT, L1D_WRITE);
  L2 = create_cache(L2_CACHE_SIZE, L2_LINE_SIZE, L2_ASSOCIATIVITY, L2_REPLACEMENT, L2_WRITE);

  instr_count = 0;
}

void memory_fetch(uint32_t* address, data_t *data)
{
  printf("memory: fetch %p\n", address);
  if (data)
    *data = (data_t)0;

  instr_count++;

  // Get index and tag from address
  bits_t index_tag = get_address_bits(L1i, *address, 0);
  element_t *cache = L1i->cache_lines;
  
}

void memory_read(double* address, data_t *data)
{
  printf("memory: read %p\n", address);
  if (data)
    *data = (data_t)0;

  instr_count++;
}

void memory_write(double* address, data_t *data)
{
  printf("memory: write %p\n", address);

  instr_count++;
}

void memory_finish(void)
{
  fprintf(stdout, "Executed %lu instructions.\n\n", instr_count);

  /* Deinitialize memory subsystem here */
}

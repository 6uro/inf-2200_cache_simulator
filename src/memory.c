/** @file memory.c
 *  @brief Implements starting point for a memory hierarchy with caching and
 * RAM.
 *  @see memory.h
 */

#include "memory.h"
#include "modify.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

static unsigned long instr_count;
static void *memory_hierarchy;

// Structures for cache, element and memory hierarchy
typedef struct cache_element element_t;
typedef struct cache_structure cache_t;
typedef struct cache_active_memory memroy_t;

// Define structs
struct cache_element {
  // Valid bit
  // Tag bit
  // Index bit
  // Offsett (?) --> uncertain if we need this
  // Dirty bit
  // "Data"
};

struct cache_structure {
  // Cache array
  // All predefined specs (?)
  // Cache Hit
  // Cache Miss
  // Hit/Miss rate (?)
  // Modulo pre-calculations (?)
};

struct cache_active_memory {
  // L1i cache
  // L1d cache
  // L2 cache
};

// Function: create a single cache structure. Also checks memory allocation success.

// Function: create a new cache element.

// Function: get index from address -> double, uint32_t

// Function: get tag from address -> double, uint32_t

void memory_init(void)
{
  // Create the memory structure
  
  // Create Caches and connect to memory structure

  instr_count = 0;
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

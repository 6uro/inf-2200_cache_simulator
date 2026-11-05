/** @file memory.c
 *  @brief Implements starting point for a memory hierarchy with caching and
 * RAM.
 *  @see memory.h
 */

#include "memory.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

static unsigned long instr_count;

void memory_init(void)
{
  /* Initialize memory subsystem here. */

  instr_count = 0;
}

void memory_fetch(uint32_t* address, data_t *data)
{
  printf("memory: fetch %p\n", address);
  if (data)
    *data = (data_t)0;

  instr_count++;
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

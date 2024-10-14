#ifndef _KERNEL_PAGING_H
#define _KERNEL_PAGING_H

#include <stdint.h>
#include <stdbool.h>

#define PAGE_SIZE 4096
#define TABLE_SIZE 1024

typedef struct {
    uint32_t present    : 1;   // Page present in memory
    uint32_t rw         : 1;   // Read-only if clear, readwrite if set
    uint32_t user       : 1;   // Supervisor level only if clear
    uint32_t accessed   : 1;   // Has the page been accessed since last refresh?
    uint32_t dirty      : 1;   // Has the page been written to since last refresh?
    uint32_t unused     : 7;   // Amalgamation of unused and reserved bits
    uint32_t frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct {
    page_t pages[1024];
} page_table_t;

typedef struct {
    page_table_t *tables[1024];
    uint32_t tablesPhysical[1024];
    uint32_t physicalAddr;
} page_directory_t;

void paging_init();
void paging_switch_directory(page_directory_t *new_directory);
page_t *paging_get_page(uint32_t address, bool make, page_directory_t *dir);
void paging_map(uint32_t va, uint32_t pa);
void paging_unmap(uint32_t va);
bool paging_is_mapped(uint32_t va);
uint32_t paging_get_physical_address(uint32_t va);

page_directory_t *paging_clone_directory(page_directory_t *src);
page_table_t *paging_clone_table(page_table_t *src, uint32_t *physAddr);
void copy_page_physical(uint32_t src, uint32_t dst);

#endif
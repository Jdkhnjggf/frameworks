
/* See LICENSE file for license and copyright information */

#ifndef LIBTEA_PAGING_IOCTL_H
#define LIBTEA_PAGING_IOCTL_H

#ifdef __cplusplus
extern "C" {
#endif

#if LIBTEA_LINUX
#include <linux/ioctl.h>
#endif

#if !defined(__KERNEL__)
#include <stdint.h>
#include "stddef.h"
#endif


/**
 * Structure containing the page-table entries of all levels.
 * The Linux names are aliased with the Intel names.
 */
typedef struct {
    /** Process ID */
    size_t pid;
    /** Virtual address */
    size_t vaddr;

    /** Page global directory / Page map level 5 */
    union {
        size_t pgd;
        size_t pml5;
    };
    /** Page directory 4 / Page map level 4 */
    union {
        size_t p4d;
        size_t pml4;
    };
    /** Page upper directory / Page directory pointer table */
    union {
        size_t pud;
        size_t pdpt;
    };
    /** Page middle directory / Page directory */
    union {
        size_t pmd;
        size_t pd;
    };
    /** Page table entry */
    size_t pte;
    /** Bitmask indicating which entries are valid/should be updated */
    size_t valid;
} libtea_page_entry;


/**
 * Structure to read/write physical pages
 */
#if LIBTEA_LINUX
typedef struct {
    /** Page-frame number */
    size_t pfn;
    /** Virtual address */
    size_t vaddr;
    /** Page size */
    size_t size;
    /** Page content */
    unsigned char* buffer;
} libtea_physical_page;
#else

#ifdef _MSC_VER
__pragma(pack(push, 1))
#else
#pragma pack(push, 1)
#endif

typedef struct {
    char content[4096];
    size_t paddr;
} libtea_physical_page;

#ifdef _MSC_VER
__pragma(pack(pop))
#else
#pragma pack(pop)
#endif

#endif


/**
 * Structure to get/set the root of paging
 */
typedef struct {
    /** Process id */
    size_t pid;
    /** Physical address of paging root */
    size_t root;
} libtea_paging_root;


#define LIBTEA_VALID_MASK_PGD (1<<0)
#define LIBTEA_VALID_MASK_P4D (1<<1)
#define LIBTEA_VALID_MASK_PUD (1<<2)
#define LIBTEA_VALID_MASK_PMD (1<<3)
#define LIBTEA_VALID_MASK_PTE (1<<4)


#ifdef __cplusplus
}
#endif

#endif //LIBTEA_PAGING_IOCTL_H

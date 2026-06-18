#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdint.h>

// ERRORS
#define ERR_SUCCESS     0 // No error
#define ERR_NULL_PTR    1 // Null ptr error
#define ERR_ALLOC_MEM   2 // Allocation or memory error
#define ERR_RANGE       3 // Bound or index error

// ERROR CHECK MACROS
#define CHK_NULL_PTR(ptr) do {if((ptr)==NULL) return ERR_NULL_PTR;}while(0)
#define CHK_INDEX(i, u) do {if((i)>=(u)) return ERR_RANGE;}while(0)
#define CHK_MEM_ALLOC(ptr) do {if((ptr)==NULL) return ERR_ALLOC_MEM;}while(0)
#define RET_SUCCESS() do {return ERR_SUCCESS;}while(0)

// TYPEDEFS
typedef uint8_t ERR_CODE;

#endif // !DEFINITIONS_H
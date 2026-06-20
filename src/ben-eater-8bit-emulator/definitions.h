#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdint.h>

// ERRORS
#define ERR_SUCCESS           0 // No error
#define ERR_NULL_PTR          1 // Null ptr error
#define ERR_ALLOC_MEM         2 // Allocation or memory error
#define ERR_RANGE             3 // Bound or index error

// CPU ERRORS
#define CPU_ERR_INVALID_INSTR 4 // Invalid operand
#define CPU_HLT               5 // Halt CPU operation

// ERROR CHECK MACROS
#define CHK_NULL_PTR(ptr) do {if((ptr)==NULL) return ERR_NULL_PTR;}while(0)
#define CHK_INDEX(i, u) do {if((i)>=(u)) return ERR_RANGE;}while(0)
#define CHK_MEM_ALLOC(ptr) do {if((ptr)==NULL) return ERR_ALLOC_MEM;}while(0)
#define RET_SUCCESS() do {return ERR_SUCCESS;}while(0)

// OPCODES
#define INSTR(op, data) (((op) << 4) | ((data) & 0x0F))
#define INSTR0(op) ((op) << 4)
#define OP_NOP 0b0000
#define OP_LDA 0b0001
#define OP_ADD 0b0010
#define OP_SUB 0b0011
#define OP_STA 0b0100
#define OP_LDI 0b0101
#define OP_JMP 0b0110
#define OP_JC  0b0111
#define OP_JZ  0b1000
#define OP_OUT 0b1110
#define OP_HLT 0b1111


// TYPEDEFS
typedef uint8_t ERR_CODE;

#endif // !DEFINITIONS_H
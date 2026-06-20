#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>
#include "definitions.h"

typedef struct {
	uint8_t PC; // Program Counter ( is 4 bits in the real ben-eater CPU )
	uint8_t IR; // Instruction Register
	uint8_t RA; // Register A
	uint8_t RB; // Register B
	uint8_t RO; // Output Register
	bool C_flag; // Carry Flag
	bool Z_flag; // Zero Flag

	uint8_t mem[16]; // Pointer to 16 bytes of memory

} Ben_Eater_CPU;

// METHODS
Ben_Eater_CPU* create_cpu();
ERR_CODE cpu_print_memory(Ben_Eater_CPU* cpu);
ERR_CODE cpu_cycle(Ben_Eater_CPU* cpu);
ERR_CODE cpu_print_state(const Ben_Eater_CPU* cpu);


// UTILS
void print_8_binary(uint8_t n);

#endif // !CPU_H
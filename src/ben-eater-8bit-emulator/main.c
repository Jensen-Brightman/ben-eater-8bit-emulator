#include <stdio.h>
#include "cpu.h"


int main() {
	Ben_Eater_CPU* my_cpu = create_cpu();

	// Example Program: Add two numbers 7 + 2
	my_cpu->mem[0] =  0b0101'0111; // LDI 7
	my_cpu->mem[1] =  0b0010'1111; // ADD* 15
	my_cpu->mem[2] =  0b1110'0000; // OUT
	my_cpu->mem[3] =  0b1111'0000; // HLT
	my_cpu->mem[15] = 0b0000'0011; // Constant 2

	cpu_print_memory(my_cpu);


	return 0;
}
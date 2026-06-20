#include <stdio.h>
#include "cpu.h"

ERR_CODE example_count_to_n(uint8_t n) {
	CHK_INDEX(n, 256);

	Ben_Eater_CPU* cpu = create_cpu();

	cpu->mem[0] = INSTR(OP_LDA, 13);
	cpu->mem[1] = INSTR(OP_ADD, 15);
	cpu->mem[2] = INSTR0(OP_OUT);
	cpu->mem[3] = INSTR(OP_STA, 13);

	cpu->mem[4] = INSTR(OP_SUB, 14);
	cpu->mem[5] = INSTR(OP_JZ, 7);
	cpu->mem[6] = INSTR(OP_JMP, 0);

	cpu->mem[7] = INSTR0(OP_HLT);

	cpu->mem[13] = 0; // i
	cpu->mem[14] = n; // n
	cpu->mem[15] = 1;

	ERR_CODE result = ERR_SUCCESS;

	while (result != CPU_HLT) {
		result = cpu_cycle(cpu);
	}

	RET_SUCCESS();
}

ERR_CODE example_add(uint8_t a, uint8_t b) {
	CHK_INDEX(a, 256);
	CHK_INDEX(b, 256);

	Ben_Eater_CPU* cpu = create_cpu();

	cpu->mem[0] = INSTR(OP_LDA, 14);
	cpu->mem[1] = INSTR(OP_ADD, 15);
	cpu->mem[2] = INSTR0(OP_OUT);
	cpu->mem[3] = INSTR0(OP_HLT);

	cpu->mem[14] = a;
	cpu->mem[15] = b;

	ERR_CODE result = ERR_SUCCESS;

	while (result != CPU_HLT) {
		result = cpu_cycle(cpu);
	}

	RET_SUCCESS();
}

ERR_CODE example_sub(uint8_t a, uint8_t b) {
	CHK_INDEX(a, 256);
	CHK_INDEX(b, 256);

	Ben_Eater_CPU* cpu = create_cpu();

	cpu->mem[0] = INSTR(OP_LDA, 14);
	cpu->mem[1] = INSTR(OP_SUB, 15);
	cpu->mem[2] = INSTR0(OP_OUT);
	cpu->mem[3] = INSTR0(OP_HLT);

	cpu->mem[14] = a;
	cpu->mem[15] = b;

	ERR_CODE result = ERR_SUCCESS;

	while (result != CPU_HLT) {
		result = cpu_cycle(cpu);
	}

	RET_SUCCESS();
}

ERR_CODE example_Fibonacci() {
	Ben_Eater_CPU* cpu = create_cpu();

	cpu->mem[0] = INSTR(OP_LDA, 15);
	cpu->mem[1] = INSTR(OP_ADD, 14);
	cpu->mem[2] = INSTR(OP_JC,  10); // Exit loop
	cpu->mem[3] = INSTR(OP_STA, 13); // temp = Y + Z

	cpu->mem[4] = INSTR0(OP_OUT);

	cpu->mem[5] = INSTR(OP_LDA, 15);
	cpu->mem[6] = INSTR(OP_STA, 14); // Z = Y

	cpu->mem[7] = INSTR(OP_LDA, 13);
	cpu->mem[8] = INSTR(OP_STA, 15); // Y = temp

	cpu->mem[9] = INSTR(OP_JMP, 0);
	
	cpu->mem[10] = INSTR0(OP_HLT);

	cpu->mem[13] = 0; // temp
	cpu->mem[14] = 0; // Z
	cpu->mem[15] = 1; // Y


	ERR_CODE result = ERR_SUCCESS;

	while (result != CPU_HLT) {
		result = cpu_cycle(cpu);
	}

	cpu_print_state(cpu);

	RET_SUCCESS();
}

int main() {
	

	//example_count_to_n(10);
	//example_add(10, 4);
	//example_sub(10, 4);

	example_Fibonacci();

	return 0;
}
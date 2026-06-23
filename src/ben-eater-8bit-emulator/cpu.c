#include <stdlib.h>
#include <stdio.h>
#include "definitions.h"
#include "cpu.h"

Ben_Eater_CPU* create_cpu() {
	Ben_Eater_CPU* cpu = malloc(sizeof(Ben_Eater_CPU));
	if (cpu == NULL) return NULL;

	cpu->PC = 0;
	cpu->IR = 0;
	cpu->RA = 0;
	cpu->RB = 0;
	cpu->RO = 0;
	cpu->C_flag = false;
	cpu->Z_flag = false;

	for (int i = 0;i < 16;i++) {
		cpu->mem[i] = 0;
	}

	return cpu;
}

ERR_CODE cpu_print_memory(Ben_Eater_CPU* cpu) {
	CHK_NULL_PTR(cpu);

	for (int i = 0; i < 16;i++) {
		printf("%d : ", i); print_8_binary(cpu->mem[i]);

		if (i == cpu->PC) printf("  <-- PC");

		printf("\n");
	}

	RET_SUCCESS();
}

ERR_CODE cpu_print_state(const Ben_Eater_CPU* cpu) {
	CHK_NULL_PTR(cpu);

	printf("Memory:\n");
	cpu_print_memory(cpu);

	printf("PC: %d\n", cpu->PC);
	printf("RA: %d\n", cpu->RA);
	printf("RB: %d\n", cpu->RB);
	printf("C_FLAG: %d\n", cpu->C_flag);
	printf("Z_FLAG: %d\n", cpu->Z_flag);

	RET_SUCCESS();
}

ERR_CODE cpu_cycle(Ben_Eater_CPU* cpu) {
	CHK_NULL_PTR(cpu);

	uint8_t IR = cpu->mem[cpu->PC];
	uint8_t opcode = (IR >> 4) & 0x0F;
	uint8_t operand = IR & 0x0F;

	switch (opcode) {
	case OP_NOP:
		cpu->PC++;
		break;
	case OP_LDA:
		cpu->RA = cpu->mem[operand];
		cpu->PC++;
		break;
	case OP_ADD:
		cpu->RB = cpu->mem[operand];
		cpu->RA = cpu->RA + cpu->RB;
		cpu->C_flag = cpu->RA < cpu->RB;
		cpu->Z_flag = cpu->RA == 0;
		cpu->PC++;
		break;
	case OP_SUB:
		cpu->RB = cpu->mem[operand];
		cpu->C_flag = (cpu->RA >= cpu->RB);
		cpu->RA = cpu->RA - cpu->RB;		
		cpu->Z_flag = cpu->RA == 0;
		cpu->PC++;
		break;
	case OP_STA:
		cpu->mem[operand] = cpu->RA;
		cpu->PC++;
		break;
	case OP_LDI:
		cpu->RA = operand;
		cpu->PC++;
		break;
	case OP_JMP:
		cpu->PC = operand;
		break;
	case OP_JC:		
		cpu->PC = cpu->C_flag ? operand : cpu->PC + 1;
		break;
	case OP_JZ:
		cpu->PC = cpu->Z_flag ? operand : cpu->PC + 1;
		break;
	case OP_OUT:
		cpu->RO = cpu->RA;
		cpu->PC++;
		printf("CPU OUT: %d\n", cpu->RO);
		break;
	case OP_HLT:
		return CPU_HLT;
	default:
		return CPU_ERR_INVALID_INSTR;
	}

	RET_SUCCESS();
}

void print_8_binary(uint8_t n) {
	for (int i = 7;i >= 0;i--) {
		int bit = (n >> i) & 1;
		printf("%d", bit);

		if (i == 4) {
			printf(" ");
		}
	}
}

void cpu_free(Ben_Eater_CPU* cpu) {
	free(cpu);
}
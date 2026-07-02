#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "definitions.h"
#include "cpu.h"

Ben_Eater_CPU* create_cpu(uint16_t clk_hz, bool cfg_debug) {
	Ben_Eater_CPU* cpu = malloc(sizeof(Ben_Eater_CPU));
	if (cpu == NULL) return NULL;

	cpu->PC = 0;
	cpu->IR = 0;
	cpu->RA = 0;
	cpu->RB = 0;
	cpu->RO = 0;
	cpu->C_flag = false;
	cpu->Z_flag = false;

	cpu->cfg_clk_speed_hz = clk_hz;
	cpu->cfg_debug = cfg_debug;

	for (int i = 0;i < 16;i++) {
		cpu->mem[i] = 0;
	}

	return cpu;
}

ERR_CODE cpu_print_memory(const Ben_Eater_CPU* cpu) {
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

static void cpu_clear_terminal() {
	system("cls");
}

static char* cpu_opcode_to_str(uint8_t opcode) {
	opcode &= 0x0F;

	switch (opcode) {
	case OP_NOP:
		return "OP_NOP";
	case OP_LDA:
		return "OP_LDA";
	case OP_ADD:
		return "OP_ADD";
	case OP_SUB:
		return "OP_SUB";
	case OP_STA:
		return "OP_STA";
	case OP_LDI:
		return "OP_LDI";
	case OP_JMP:
		return "OP_JMP";
	case OP_JC:
		return "OP_JC ";
	case OP_JZ:
		return "OP_JZ ";
	case OP_OUT:
		return "OP_OUT";
	case OP_HLT:
		return "OP_HLT";
	default:
		return "INV_OP";
	}
}

static int count_digits(int x) {
	if (x == 0) return 1;
	int count = 0;

	while (x != 0) {
		x /= 10;
		count++;
	}

	return count;
}

static ERR_CODE cpu_debug(const Ben_Eater_CPU* cpu) {
	CHK_NULL_PTR(cpu);
	cpu_clear_terminal();

	printf("Memory:\n");
	for (int i = 0; i < 16;i++) {
		printf("%d ", i); if (i < 10) printf(" "); printf(": ");
		print_8_binary(cpu->mem[i]);
		printf("  (%s", cpu_opcode_to_str(cpu->mem[i] >> 4));

		uint8_t operand = cpu->mem[i] & 0x0F;
		printf(" %d)", operand); if (operand < 10) printf(" ");
		printf("  %d", cpu->mem[i]);

		for (int x = 0; x < (3 - count_digits(cpu->mem[i]));x++) {
			printf(" ");
		}

		if (i == cpu->PC) printf("  <-- PC");

		printf("\n");
	}

	printf("\nRegisters\n");
	printf("PC: %d\n", cpu->PC);
	printf("RA: %d\n", cpu->RA);
	printf("RB: %d\n", cpu->RB);
	printf("C_FLAG: %d\n", cpu->C_flag);
	printf("Z_FLAG: %d\n", cpu->Z_flag);

	RET_SUCCESS();
}

ERR_CODE cpu_cycle(Ben_Eater_CPU* cpu) {
	CHK_NULL_PTR(cpu);

	if (cpu->cfg_debug) cpu_debug(cpu);

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
		if (!cpu->cfg_debug) printf("CPU OUT: %d\n", cpu->RO);
		break;
	case OP_HLT:
		return CPU_HLT;
	default:
		return CPU_ERR_INVALID_INSTR;
	}

	Sleep(1000 / cpu->cfg_clk_speed_hz);

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
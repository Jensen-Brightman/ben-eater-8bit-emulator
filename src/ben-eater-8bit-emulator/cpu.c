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
		printf("%d : ", i); print_8_binary(cpu->mem[i]); printf("\n");
	}

	RET_SUCCESS();
}

void print_8_binary(uint8_t n) {
	for (int i = 7;i >= 0;i--) {
		int bit = (n >> i) & 1;
		printf("%d", bit);

		if (i==4) {
			printf(" ");
		}
	}
}
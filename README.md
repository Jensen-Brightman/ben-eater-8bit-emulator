# Ben Eater 8-Bit Emulator
A simple C emulator for Ben Eater's standard 8-bit CPU.
**Reference:** [Ben Eater's CPU Video Series](https://www.youtube.com/c/BenEater)

## Features
- **Configurable clock speed:** Throttle execution speed to watch operations happen in real time.
- **Telemetry & Debugging:** Visualizes the full system state: registers, flags and memory on each clock cycle.
- **Manual clock:** _[Planned]_

## Ben Eater's CPU
Ben Eater's CPU is a version of the SAP-1 (Simple-As-Possible) computer. Specifics include:
- **Memory:** 16 bytes of RAM.
- **Registers:** 4 primary 8-bit registers.
  1. Register/accumulator: Register A **[RA]**.
  2. ALU input: Register B **[RB]**.
  3. Instruction register **[IR]**.
  4. Output Register **[RO]**.
- **Instruction Format:** 8-bit instructions split into two 4-bit nibbles: `[opcode][operand]`.
- **Shared Bus:** A central 8-bit bus connecting components together.

## Usage
To create an instance, use the constructor 
```c
Ben_Eater_CPU* cpu = create_cpu(uint16_t cfg_clk_speed_hz, bool cfg_debug);
```
When `cfg_debug` is true, the emulator displays a table in the terminal each cycle showing the state of memory and registers.  
Populate memory with instructions using `INSTR(opcode, data)` and `INSTR0(opcode)` for simplicity. Then call `cpu_cycle(cpu);` for each iteration. Below is an example of a simple program to add two integers, `a` and `b`.
```c
Ben_Eater_CPU* cpu = create_cpu(1, true);

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

cpu_free(cpu);
```

## Example
Here is an example of the emulator running a program that calculates the Fibonacci sequence until the result exceeds what can be represented in a single byte. The memory table follows the format:  
`[index] : [binary representation] ([instruction represented by first nibble] [data in second nibble]) [denary of whole byte]`  
In some cases the denary version of the whole byte may be relevant if it's used for data, while only the instruction and data interpretation is relevant when that byte represents an instruction rather than data.
```
Memory:
0  : 0001 1111  (OP_LDA 15)  31
1  : 0010 1110  (OP_ADD 14)  46
2  : 0111 1010  (OP_JC  10)  122
3  : 0100 1101  (OP_STA 13)  77
4  : 1110 0000  (OP_OUT 0)   224
5  : 0001 1111  (OP_LDA 15)  31
6  : 0100 1110  (OP_STA 14)  78
7  : 0001 1101  (OP_LDA 13)  29
8  : 0100 1111  (OP_STA 15)  79
9  : 0110 0000  (OP_JMP 0)   96
10 : 1111 0000  (OP_HLT 0)   240  <-- PC
11 : 0000 0000  (OP_NOP 0)   0
12 : 0000 0000  (OP_NOP 0)   0
13 : 1110 1001  (OP_OUT 9)   233
14 : 1001 0000  (INV_OP 0)   144
15 : 1110 1001  (OP_OUT 9)   233

Registers
PC: 10
RA: 121
RB: 144
C_FLAG: 1
Z_FLAG: 0
```

## Functions
Below is a full list of functions included in cpu.h  
`Ben_Eater_CPU* create_cpu(uint16_t clk_hz, bool cfg_debug);`  
`ERR_CODE cpu_print_memory(const Ben_Eater_CPU* cpu);`  
`ERR_CODE cpu_cycle(Ben_Eater_CPU* cpu);`  
`ERR_CODE cpu_print_state(const Ben_Eater_CPU* cpu);`  
`void cpu_free(Ben_Eater_CPU* cpu);`  
`void print_8_binary(uint8_t n);`  

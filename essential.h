#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
//well lets start easy first;;;

typedef struct Flags{
    unsigned int C: 1;
    unsigned int Z : 1;
    unsigned int I : 1;
    unsigned int D : 1;
    unsigned int B : 1;
    unsigned int V : 1;
    unsigned int N : 1;
    //Carry, Zero, Interrupt_disable, Decimal, Break, Overflow, Negetive
}Flags;


typedef struct interrupts{
   //add the interrupts
}interrupts;


typedef struct Register{
    int8_t accumulator;
    int8_t x_register;
    int8_t y_register;
}Register;

typedef struct cpu6502{
    //since memory can be of one byte
    uint8_t *memory;
    Flags flags;
    Register r;
    uint16_t PC; //points to the next instruction to be excuted so current_instruction + 1.
    uint8_t SP; //stack pointer
    uint32_t cycles;
}cpu6502;

void initialize(cpu6502 *cpu);
void write_memory(cpu6502 *cpu, uint16_t address, uint8_t value);//<- honestly useless
void display_memory(cpu6502 *cpu, uint16_t address);
uint8_t read_memory(cpu6502 *cpu, uint16_t address);
void del(cpu6502 *cpu);
void execute_instruction(cpu6502 *cpu);
void display_status_signals(cpu6502 *cpu);
void display_register(cpu6502 *cpu);
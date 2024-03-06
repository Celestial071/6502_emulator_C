#include "essential.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

void initialize(cpu6502 *cpu){
    //memory initialization
    cpu->memory = calloc(65536, sizeof(uint8_t));
    //setting all cpu flags to 0
    cpu->flags.C = 0;
    cpu->flags.Z = 0;
    cpu->flags.I = 0;
    cpu->flags.D = 0;
    cpu->flags.B = 0;
    cpu->flags.V = 0;
    cpu->flags.N = 0;
    //setting all the registers to 0
    cpu->r.accumulator = 0;
    cpu->r.x_register = 0;
    cpu->r.y_register = 0;
    //implement the stack
}


void write_memory(cpu6502 *cpu, uint16_t address, uint8_t value){
    cpu->memory[address] = value;
}

//change this address format in interger into hex (easy)
void display_memory(cpu6502 *cpu, uint16_t address){
    printf("in memory %04X there is value %02X\n",address, cpu->memory[address]);
}

uint8_t read_memory(cpu6502 *cpu, uint16_t address){
    return cpu->memory[address];
}

void del(cpu6502 *cpu){
    free(cpu);
}

void execute_instruction(cpu6502 *cpu){
    uint8_t opcode = read_memory(cpu, cpu->PC++);
    switch(opcode){
        //this is me implementing all the LDA instructions (without ones which can pagefault)
        case 0xA9: //example: LDA Immediate
            cpu->r.accumulator = read_memory(cpu, cpu->PC++);
            cpu->flags.N = (cpu->r.accumulator >> 7) & 1? 1:0;
            cpu->flags.Z = cpu->r.accumulator == 0;
            cpu->cycles += 2;
            break;
        //lets do absolute
        case 0xAD:{ //LDA absolute <-- 4 cpu cycle
            uint16_t temp_addr = 0;
            temp_addr = read_memory(cpu, cpu->PC++);
            temp_addr = (temp_addr << 8) | read_memory(cpu, cpu->PC++);
            cpu->r.accumulator = read_memory(cpu, temp_addr);
            cpu->flags.N = (cpu->r.accumulator >> 7) & 1? 1:0;
            cpu->flags.Z = cpu->r.accumulator == 0;
            cpu->cycles += 4;
            break;
        }
        case 0xA5:{ //LDA zero page
            uint8_t zeroPageAddr = read_memory(cpu, cpu->PC++);
            if(zeroPageAddr >=0x00 && zeroPageAddr <= 0xFF){
                cpu->r.accumulator = read_memory(cpu, zeroPageAddr);
                cpu->flags.N = (cpu->r.accumulator >> 7) & 1? 1:0;
                cpu->flags.Z = cpu->r.accumulator == 0;
                cpu->cycles += 3;
            }
            break;
        }

        case 0xB5:{ //zero page, X
            uint8_t zeroPageAddr = read_memory(cpu, cpu->PC++);
            uint8_t effectiveAddr = (zeroPageAddr + cpu->r.x_register) & 0xFF;
            cpu->r.accumulator = read_memory(cpu, effectiveAddr);
            cpu->flags.N = (cpu->r.accumulator >> 7) & 1? 1:0;
            cpu->flags.Z = cpu->r.accumulator == 0;
            cpu->cycles += 4;
        }
        default:
            printf("Invalid instruction! %2X\n", opcode);
            break;
    }       
}

void display_register(cpu6502 *cpu){
    printf("Accumulator:- %d\tX-register:- %d\tY-register:- %d\n", cpu->r.accumulator, cpu->r.x_register, cpu->r.y_register);
}

void display_status_signals(cpu6502 *cpu){
    printf("C = %d\tZ = %d\tI = %d\tD = %d\tB = %d\tV = %d\tN = %d\n", cpu->flags.C\
    ,cpu->flags.Z,\
    cpu->flags.I,\
    cpu->flags.D,\
    cpu->flags.B,\
    cpu->flags.V,\
    cpu->flags.N);
}
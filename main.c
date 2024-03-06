#include "essential.h"

int main(){
    cpu6502 myCpu;
    initialize(&myCpu);
    //lets add the instuction we just added in our emulator
   // write_memory(&myCpu, 0x0000, 0xA9);
    myCpu.memory[0x0000] = 0xA9;
    myCpu.PC = 0x0000;
    //write_memory(&myCpu,0x0001 , 255);
    myCpu.memory[0x0001] = 0xFF;
    execute_instruction(&myCpu);
    display_memory(&myCpu, 0x0000);
    display_memory(&myCpu, 0x0001);
    display_register(&myCpu);
    display_status_signals(&myCpu);
    return 0;
}
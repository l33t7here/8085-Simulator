#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "microProcessor.h"

typedef struct instruction_set{
    bool (*func)(_8085MP *Machine);
    address operandInfo;

}instruction_set;

// All Individual Functions 
static bool lxi_b(_8085MP *Machine);
static bool hlt(_8085MP *Machine);
static bool nop();
static bool stax_b(_8085MP *Machine);
static bool inx_b(_8085MP *Machine);
static bool inr_b(_8085MP *Machine);
static bool dcr_b(_8085MP *Machine);
static bool mvi_b(_8085MP *Machine);
static bool rlc(_8085MP *Machine);
static bool invalid(_8085MP *Machine);
static bool dad_b(_8085MP *Machine);
static bool ldax_b(_8085MP *Machine);
static bool dcx_b(_8085MP *Machine);
static bool inr_c(_8085MP *Machine);
static bool dcr_c(_8085MP *Machine);
static bool mvi_c(_8085MP *Machine);
static bool rrc(_8085MP *Machine);
static bool lxi_d(_8085MP *Machine);
static bool stax_d(_8085MP *Machine);
static bool inx_d(_8085MP *Machine);
static bool inr_d(_8085MP *Machine);
static bool dcr_d(_8085MP *Machine);
static bool mvi_d(_8085MP *Machine);
static bool ral(_8085MP *Machine);
static bool dad_d(_8085MP *Machine);
static bool ldax_d(_8085MP *Machine);
static bool dcx_d(_8085MP *Machine);
static bool inr_e(_8085MP *Machine);
static bool dcr_e(_8085MP *Machine);
static bool mvi_e(_8085MP *Machine);
static bool rar(_8085MP *Machine);
static bool rim(_8085MP *Machine);
static bool lxi_h(_8085MP *Machine);
static bool shld(_8085MP *Machine);
static bool inx_h(_8085MP *Machine);
static bool inr_h(_8085MP *Machine);
static bool dcr_h(_8085MP *Machine);
static bool mvi_h(_8085MP *Machine);
static bool daa(_8085MP *Machine);



// All Helper Function Defined
static data getoperand(_8085MP *Machine);
static address pair_data_get(data lower, data higher);
static void pair_data_set(data *higher, data *lower, address value);
static bool pairAdder(_8085MP *Machine, data higher, data lower);
// Flag Section
static void setCarry(_8085MP *Machine){
    // Position Of Carry Flag
    Machine->flag = Machine->flag | 0x01;
}
static void resetCarry(_8085MP *Machine){
    // Position Of Carry Flag
    Machine->flag = Machine->flag & 0xFE;
}
static data getCarry(_8085MP *Machine){
    return Machine->flag & 0x01;
}

static void setParity(_8085MP *Machine){
    // Position Of Carry Flag
    Machine->flag = Machine->flag | 0x04;
}
static void resetParity(_8085MP *Machine){
    // Position Of Carry Flag
    Machine->flag = Machine->flag & 0xFB;
}
static data getParity(_8085MP *Machine){
    return Machine->flag & 0x04;
}

static void setAC(_8085MP *Machine){
    // Position Of Carry Flag
    Machine->flag = Machine->flag | 0x10;
}
static void resetAC(_8085MP *Machine){
    // Position Of Carry Flag
    Machine->flag = Machine->flag & 0xEF;
}
static data getAC(_8085MP *Machine){
    return Machine->flag & 0x10;
}

static void setZero(_8085MP *Machine){
    // Position Of Carry Flag
    Machine->flag = Machine->flag | 0x40;
}
static void resetZero(_8085MP *Machine){
    // Position Of Carry Flag
    Machine->flag = Machine->flag & 0xBF;
}
static data getZero(_8085MP *Machine){
    return Machine->flag & 0x40;
}

static void setSign(_8085MP *Machine){
    // Position Of Carry Flag
    Machine->flag = Machine->flag | 0x80;
}
static void resetSign(_8085MP *Machine){
    // Position Of Carry Flag
    Machine->flag = Machine->flag & 0x7F;
}
static data getSign(_8085MP *Machine){
    return Machine->flag & 0x80;
}


static void clearFlags(_8085MP *Machine){
    Machine->flag = 0x00;
}

static data ALU(_8085MP *Machine,data operand2, bool add, data *anyOtherRegister){
    if(!add){
        // 2's Complement of Operand 2 then add
        operand2 = (operand2 ^ 0xff) + 0x01;
    }
    // Normal Addition And Also Check All Flags 
    // Perform Addition Via Custom Adder
    data carry = 0x00;
    data ac = 0x00;
    data sum = 0x00;
    data parity = 0xff;
    data operand1 = (!anyOtherRegister) ? Machine->a : *(anyOtherRegister); 
    for (int j = 0;  j < 8;  ++j){
        int op1nBit = 0 != (operand1 & (1 << j));
        int op2nBit = 0 != (operand2 & (1 << j));
        if(op1nBit ^ carry ^ op2nBit){
            sum = sum | (0x01 << j);
            parity = ~parity;
        }
        carry = (op1nBit & op2nBit) | carry & (op1nBit | op2nBit);
        (j == 3 & carry) ? ac  = 1 : 0;
     }
    if(!anyOtherRegister)
        Machine->a = sum;
    else
        (*(anyOtherRegister)) = sum;
    // Carry Flag Check
     (carry && !anyOtherRegister) ? setCarry(Machine) : resetCarry(Machine);
    
    //AC Flag Check
    (ac) ? setAC(Machine) : resetAC(Machine);
     
     // Parity Check
     (parity) ? setParity(Machine) : resetParity(Machine);
     
     // Zero Flag Check
     (sum) ? resetZero(Machine) : setZero(Machine);
     // Sign Flag
     (sum & 0x80) ? setSign(Machine) : resetSign(Machine); 
     return sum;
}
// static void set_bc_pair()
// Instruction Sets With Indexing of HexCodes :)
static instruction_set allInstruction[0xff] = {
    {hlt}, //0x00 change it with nop 
    {lxi_b}, //0x01
    {stax_b}, //0x02
    {inx_b}, //0x03
    {inr_b},//0x04
    {dcr_b},//0x05
    {mvi_b},//0x06
    {rlc},//0x07
    {invalid},//0x08
    {dad_b},//0x09
    {ldax_b},//0x0A
    {dcx_b},  
    {inr_c},
    {dcr_c},
    {mvi_c},
    {rrc},
    {invalid},
    {lxi_d},
    {stax_d},
    {inx_d},
    {inr_d},
    {dcr_d},
    {mvi_d},
    {ral},
    {invalid},
    {dad_d},
    {ldax_d},
    {dcx_d},
    {inr_e},
    {dcr_e},
    {mvi_e},
    {rar},
    {rim},
    {lxi_h},
    {shld},
    {inx_h},
    {inr_h},
    {dcr_h},
    {mvi_h},
    {daa}
};

static bool nop(){
    return true;
}
static bool lxi_b(_8085MP *Machine){
    // printf("I ran");
    Machine->c = getoperand(Machine);
    Machine->b = getoperand(Machine);
    return true;
}
static bool stax_b(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->c, Machine->b)] = Machine->a;
    return true;
};
static bool inr_b(_8085MP *Machine){
    // Do Not Change Carry Flag
    ALU(Machine, 0x01, true, &(Machine->b));
    return true;
}
static bool dcr_b(_8085MP *Machine){
    ALU(Machine, 0x01, false,&(Machine->b));
    return true;
}
static bool inx_b(_8085MP *Machine){
    // Does Not Affect Any Flag
    pair_data_set(&Machine->b, &Machine->c, pair_data_get(Machine->c, Machine->b) + 0x01);
    return true;
}
static bool mvi_b(_8085MP *Machine){
    Machine->b  = getoperand(Machine);
    return true;
}
static bool rlc(_8085MP *Machine){
    if(Machine->a & 0x80)
        setCarry(Machine);
    else
        resetCarry(Machine);
    Machine->a <<= 1;
    return true;
}
static bool dad_b(_8085MP *Machine){
    return pairAdder(Machine, Machine->b, Machine->c);
}
static bool ldax_b(_8085MP *Machine){
    Machine->a = Machine->memory[pair_data_get(Machine->c, Machine->b)];
    return true;    
}
static bool dcx_b(_8085MP *Machine){
    // Does Not Affect Any Flag
    pair_data_set(&Machine->b, &Machine->c, pair_data_get(Machine->c, Machine->b) - 0x01);
    return true;
}
static bool inr_c(_8085MP *Machine){
    ALU(Machine, 0x01, true, &(Machine->c));
    return true;
}   
static bool dcr_c(_8085MP *Machine){
    ALU(Machine, 0x01, false, &Machine->c);
    return true;
}
static bool mvi_c(_8085MP *Machine){
    Machine->c = getoperand(Machine);
    return true;
}
static bool rrc(_8085MP *Machine){
    if(Machine->a & 0x01)
        setCarry(Machine);
    else
        resetCarry(Machine);
    Machine->a >>= 1;
    return true;
}

static bool lxi_d(_8085MP *Machine){
    // printf("I ran");
    Machine->d = getoperand(Machine);
    Machine->e = getoperand(Machine);
    return true;
}
static bool stax_d(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->e, Machine->d)] = Machine->a;
    return true;
};
static bool inr_d(_8085MP *Machine){
    // Do Not Change Carry Flag
    ALU(Machine, 0x01, true, &Machine->d);
    return true;
}
static bool dcr_d(_8085MP *Machine){
    ALU(Machine, 0x01, false,&Machine->d);
    return true;
}
static bool inx_d(_8085MP *Machine){
    // Does Not Affect Any Flag
    pair_data_set(&Machine->b, &Machine->c, pair_data_get(Machine->e, Machine->d) + 0x01);
    return true;
}
static bool mvi_d(_8085MP *Machine){
    Machine->d  = getoperand(Machine);
    return true;
}
static bool ral(_8085MP *Machine){
    data carryFlag = getCarry(Machine);
    if(Machine->a & 0x80)
        setCarry(Machine);
    else
        resetCarry(Machine);
    Machine->a <<= 1;
    Machine->a |= carryFlag;
    return true;
}
static bool dad_d(_8085MP *Machine){
    return pairAdder(Machine, Machine->d, Machine->e);
}
static bool ldax_d(_8085MP *Machine){
    Machine->a = Machine->memory[pair_data_get(Machine->e, Machine->d)];
    return true;    
}
static bool dcx_d(_8085MP *Machine){
    // Does Not Affect Any Flag
    pair_data_set(&Machine->d, &Machine->e, pair_data_get(Machine->e, Machine->d) - 0x01);
    return true;
}

static bool inr_e(_8085MP *Machine){
    ALU(Machine, 0x01, true, &Machine->e);
    return true;
}   
static bool dcr_e(_8085MP *Machine){
    ALU(Machine, 0x01, false, &Machine->e);
    return true;
}
static bool mvi_e(_8085MP *Machine){
    Machine->e = getoperand(Machine);
    return true;
}
static bool rar(_8085MP *Machine){
    data carryFlag = getCarry(Machine); 
    if(Machine->a & 0x01)
        setCarry(Machine);
    else
        resetCarry(Machine);
    Machine->a >>= 1;
    Machine->a |= (carryFlag) ? 0x80 : 0x00;
    return true;
}
// RIM -> NEXT UPDATE 
static bool rim(_8085MP *Machine){
    return true;
}

static bool lxi_h(_8085MP *Machine){
    // printf("I ran");
    Machine->l = getoperand(Machine);
    Machine->h = getoperand(Machine);
    return true;
}
static bool shld(_8085MP *Machine){
    // printf("I ran");
    data lowerByte = getoperand(Machine);
    data higherByte = getoperand(Machine);
    Machine->memory[pair_data_get(lowerByte, higherByte)] = Machine->l;
    Machine->memory[pair_data_get(lowerByte, higherByte) + 1] = Machine->h;
    return true;
}
static bool inx_h(_8085MP *Machine){
    // Does Not Affect Any Flag
    pair_data_set(&Machine->h, &Machine->l, pair_data_get(Machine->l, Machine->h) + 0x01);
    return true;
}
static bool inr_h(_8085MP *Machine){
    // Do Not Change Carry Flag
    ALU(Machine, 0x01, true, &Machine->h);
    return true;
}
static bool dcr_h(_8085MP *Machine){
    ALU(Machine, 0x01, false,&Machine->h);
    return true;
}

static bool mvi_h(_8085MP *Machine){
    Machine->h = getoperand(Machine);
    return true;
}
static bool daa(_8085MP *Machine){
    if(((Machine->a & 0x0f) > 0x09) || getAC(Machine))
        ALU(Machine, 0x06, true, NULL);
    if(((Machine->a & 0xf0) > 0x09) || getCarry(Machine))
        ALU(Machine, 0x60, true, NULL);
    return true;
}
static bool dad_h(_8085MP *Machine){
    return pairAdder(Machine, Machine->h, Machine->l);
}
static bool lhld(_8085MP *Machine){
    // printf("I ran");
    data lowerByte = getoperand(Machine);
    data higherByte = getoperand(Machine);
    Machine->l = Machine->memory[pair_data_get(lowerByte, higherByte)];
    Machine->h = Machine->memory[pair_data_get(lowerByte, higherByte) + 1];
    return true;
}
static bool dcx_h(_8085MP *Machine){
    // Does Not Affect Any Flag
    pair_data_set(&Machine->h, &Machine->l, pair_data_get(Machine->l, Machine->h) - 0x01);
    return true;
}
static bool inr_l(_8085MP *Machine){
    // Do Not Change Carry Flag
    ALU(Machine, 0x01, true, &Machine->l);
    return true;
}
static bool dcr_l(_8085MP *Machine){
    ALU(Machine, 0x01, false,&Machine->l);
    return true;
}

static bool mvi_l(_8085MP *Machine){
    Machine->l = getoperand(Machine);
    return true;
}
static bool cma(_8085MP *Machine){
    Machine->a = ~Machine->a;
    return true;
}
// SIM NEXT UPDATE
static bool sim(_8085MP *Machine){
    return true;
}

static bool lxi_sp(_8085MP *Machine){
    data lowerByte = getoperand(Machine);
    data higherByte = getoperand(Machine);
    Machine->sp = higherByte;
    Machine->sp <<= 8;
    Machine->sp |= lowerByte;
    return true;
}
static bool inx_sp(_8085MP *Machine){
    Machine->sp = Machine->sp + 0x01;
    return true;
}
static bool inr_m(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->l, Machine->h)]++;
    return true;
}

static bool dcr_m(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->l, Machine->h)]--;
    return true;
}
static bool mvi_m(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->l, Machine->h)] = getoperand(Machine);
    return true;
}
static bool stc(_8085MP *Machine){
    setCarry(Machine);
    return true;
}

static bool dad_sp(_8085MP *Machine){
    return pairAdder(Machine, Machine->sp >> 8, Machine->sp);
}
static bool lda(_8085MP *Machine){
   Machine->a = Machine->memory[pair_data_get(getoperand(Machine), getoperand(Machine))];
   return true;
}
static bool dcx_sp(_8085MP *Machine){
    Machine->sp = Machine->sp - 0x01;
    return true;
}
static bool inr_a(_8085MP *Machine){
    // Do Not Change Carry Flag
    ALU(Machine, 0x01, true, &Machine->a);
    return true;
}
static bool dcr_a(_8085MP *Machine){
    // Do Not Change Carry Flag
    ALU(Machine, 0x01, false, &Machine->a);
    return true;
}
static bool mvi_a(_8085MP *Machine){
    Machine->a = getoperand(Machine);
    return true;
}
static bool cmc(_8085MP *Machine){
    if(getCarry(Machine))
        resetCarry(Machine);
    else
        setCarry(Machine);
    return true;
}
static bool mov_b_b(_8085MP *Machine){
    Machine->b = Machine->b;
    return true;
}
static bool mov_b_c(_8085MP *Machine){
    Machine->b = Machine->c;
    return true;
}
static bool mov_b_d(_8085MP *Machine){
    Machine->b = Machine->d;
    return true;
}
static bool mov_b_e(_8085MP *Machine){
    Machine->b = Machine->e;
    return true;
}
static bool mov_b_h(_8085MP *Machine){
    Machine->b = Machine->h;
    return true;
}
static bool mov_b_l(_8085MP *Machine){
    Machine->b = Machine->l;
    return true;
}
static bool mov_b_m(_8085MP *Machine){
    Machine->b = Machine->memory[pair_data_get(Machine->l, Machine->h)];
    return true;
}
static bool mov_b_a(_8085MP *Machine){
    Machine->b = Machine->a;
    return true;
}
static bool mov_c_b(_8085MP *Machine){
    Machine->c = Machine->b;
    return true;
}
static bool mov_c_c(_8085MP *Machine){
    Machine->c = Machine->c;
    return true;
}
static bool mov_c_d(_8085MP *Machine){
    Machine->c = Machine->d;
    return true;
}
static bool mov_c_e(_8085MP *Machine){
    Machine->c = Machine->e;
    return true;
}
static bool mov_c_h(_8085MP *Machine){
    Machine->c = Machine->h;
    return true;
}
static bool mov_c_l(_8085MP *Machine){
    Machine->c = Machine->l;
    return true;
}
static bool mov_c_m(_8085MP *Machine){
    Machine->c = Machine->memory[pair_data_get(Machine->l, Machine->h)];
    return true;
}
static bool mov_c_a(_8085MP *Machine){
    Machine->c = Machine->a;
    return true;
}
static bool mov_d_b(_8085MP *Machine){
    Machine->d = Machine->b;
    return true;
}
static bool mov_d_c(_8085MP *Machine){
    Machine->d = Machine->c;
    return true;
}
static bool mov_d_d(_8085MP *Machine){
    Machine->d = Machine->d;
    return true;
}
static bool mov_d_e(_8085MP *Machine){
    Machine->d = Machine->e;
    return true;
}
static bool mov_d_h(_8085MP *Machine){
    Machine->d = Machine->h;
    return true;
}
static bool mov_d_l(_8085MP *Machine){
    Machine->d = Machine->l;
    return true;
}
static bool mov_d_m(_8085MP *Machine){
    Machine->d = Machine->memory[pair_data_get(Machine->l, Machine->h)];
    return true;
}
static bool mov_d_a(_8085MP *Machine){
    Machine->d = Machine->a;
    return true;
}
static bool mov_e_b(_8085MP *Machine){
    Machine->e = Machine->b;
    return true;
}
static bool mov_e_c(_8085MP *Machine){
    Machine->e = Machine->c;
    return true;
}
static bool mov_e_d(_8085MP *Machine){
    Machine->e = Machine->d;
    return true;
}
static bool mov_e_e(_8085MP *Machine){
    Machine->e = Machine->e;
    return true;
}
static bool mov_e_h(_8085MP *Machine){
    Machine->e = Machine->h;
    return true;
}
static bool mov_e_l(_8085MP *Machine){
    Machine->e = Machine->l;
    return true;
}
static bool mov_e_m(_8085MP *Machine){
    Machine->e = Machine->memory[pair_data_get(Machine->l, Machine->h)];
    return true;
}
static bool mov_e_a(_8085MP *Machine){
    Machine->e = Machine->a;
    return true;
}
static bool mov_h_b(_8085MP *Machine){
    Machine->h = Machine->b;
    return true;
}
static bool mov_h_c(_8085MP *Machine){
    Machine->h = Machine->c;
    return true;
}
static bool mov_h_d(_8085MP *Machine){
    Machine->h = Machine->d;
    return true;
}
static bool mov_h_e(_8085MP *Machine){
    Machine->h = Machine->e;
    return true;
}
static bool mov_h_h(_8085MP *Machine){
    Machine->h = Machine->h;
    return true;
}
static bool mov_h_l(_8085MP *Machine){
    Machine->h = Machine->l;
    return true;
}
static bool mov_h_m(_8085MP *Machine){
    Machine->h = Machine->memory[pair_data_get(Machine->l, Machine->h)];
    return true;
}
static bool mov_h_a(_8085MP *Machine){
    Machine->h = Machine->a;
    return true;
}
static bool mov_l_b(_8085MP *Machine){
    Machine->l = Machine->b;
    return true;
}
static bool mov_l_c(_8085MP *Machine){
    Machine->l = Machine->c;
    return true;
}
static bool mov_l_d(_8085MP *Machine){
    Machine->l = Machine->d;
    return true;
}
static bool mov_l_e(_8085MP *Machine){
    Machine->l = Machine->e;
    return true;
}
static bool mov_l_h(_8085MP *Machine){
    Machine->l = Machine->h;
    return true;
}
static bool mov_l_l(_8085MP *Machine){
    Machine->l = Machine->l;
    return true;
}
static bool mov_l_m(_8085MP *Machine){
    Machine->l = Machine->memory[pair_data_get(Machine->l, Machine->h)];
    return true;
}
static bool mov_l_a(_8085MP *Machine){
    Machine->l = Machine->a;
    return true;
}
static bool mov_m_b(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->l, Machine->h)] = Machine->b;
    return true;
}
static bool mov_m_c(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->l, Machine->h)] = Machine->c;
    return true;
}
static bool mov_m_d(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->l, Machine->h)] = Machine->d;
    return true;
}
static bool mov_m_e(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->l, Machine->h)] = Machine->e;
    return true;
}
static bool mov_m_h(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->l, Machine->h)] = Machine->h;
    return true;
}
static bool mov_m_l(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->l, Machine->h)] = Machine->l;
    return true;
}
// HLT
static bool mov_m_a(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->l, Machine->h)] = Machine->a;
    return true;
}
static bool mov_a_b(_8085MP *Machine){
    Machine->a = Machine->b;
    return true;
}
static bool mov_a_c(_8085MP *Machine){
    Machine->a = Machine->c;
    return true;
}
static bool mov_a_d(_8085MP *Machine){
    Machine->a = Machine->d;
    return true;
}
static bool mov_a_e(_8085MP *Machine){
    Machine->a = Machine->e;
    return true;
}
static bool mov_a_h(_8085MP *Machine){
    Machine->a = Machine->h;
    return true;
}
static bool mov_a_l(_8085MP *Machine){
    Machine->a = Machine->l;
    return true;
}
static bool mov_a_m(_8085MP *Machine){
    Machine->a = Machine->memory[pair_data_get(Machine->l, Machine->h)];
    return true;
}
static bool mov_a_a(_8085MP *Machine){
    Machine->a = Machine->a;
    return true;
}

static bool invalid(_8085MP *Machine){
    printf("Invalid OpCode");
    return false;
}
static bool hlt(_8085MP *Machine){
    printf("Program Terminated Successfull\n");
    return false;
}

// Helper Function 
static void starttup(_8085MP *Machine, address start){
    Machine->instruction_register = start;
    Machine->pc = start;
}
static data getoperand(_8085MP *Machine){
    return Machine->memory[++Machine->pc];
}
static address pair_data_get(data lower, data higher){
    address returnValue = higher;
    returnValue <<= 8; // 8 Bit Shifted 
    returnValue |= lower;
    return returnValue;
}

static void pair_data_set(data *higher, data *lower, address value){
    *higher = (value >> 8);
    *lower = (value);
}

static bool pairAdder(_8085MP *Machine, data higher, data lower){
    address Sum = Machine->l + lower;
    Machine->l = Sum;
    Sum >>= 8;
    Sum = Sum + Machine->h + higher;
    Machine->h = Sum;
    if(Sum >> 8)
        setCarry(Machine);
    else
        resetCarry(Machine);
    return true;
    
}

// Public Exposed Function
_8085MP* createNewMachine(){
    _8085MP *newMachine = (_8085MP *)malloc(sizeof(_8085MP));
    newMachine->a = 0;
    newMachine->b = 0;
    newMachine->c = 0;
    newMachine->d = 0;
    newMachine->e = 0;
    newMachine->flag = 0;
    newMachine->h = 0;
    newMachine->l = 0;
    newMachine->pc = 0;
    newMachine->sp = 0;
    newMachine->memory = (data *)calloc(10000, sizeof(data));
    return newMachine;    
}

bool execute(_8085MP *machine, address start_address){
    starttup(machine, start_address);
    bool ranSuccessfully = false;
    do{ 
        ranSuccessfully = allInstruction[machine->memory[machine->instruction_register]].func(machine);
        machine->instruction_register = ++machine->pc;
    }while(ranSuccessfully);
}



int main(){
    _8085MP *newMachine = createNewMachine();
    //newMachine->memory[0x0fff] = 0x07;
    newMachine->a = 0x0b;
    // newMachine->memory[0] = 0x01;
    // newMachine->memory[1] = 0xff;  
    // newMachine->memory[2] = 0x07;
    // newMachine->memory[3] = 0x09;
    newMachine->memory[0] = 0x27;
    newMachine->memory[1] = 0x00;
    execute(newMachine, 0x00);
    printf("%x", newMachine->a);
    return 0;
}


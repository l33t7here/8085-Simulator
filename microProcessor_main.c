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
static bool dad_h(_8085MP *Machine);
static bool lhld(_8085MP *Machine);
static bool dcx_h(_8085MP *Machine);
static bool inr_l(_8085MP *Machine);
static bool dcr_l(_8085MP *Machine);
static bool mvi_l(_8085MP *Machine);
static bool cma(_8085MP *Machine);
static bool sim(_8085MP *Machine);
static bool lxi_sp(_8085MP *Machine);
static bool sta(_8085MP *Machine);
static bool inx_sp(_8085MP *Machine);
static bool inr_m(_8085MP *Machine);
static bool dcr_m(_8085MP *Machine);
static bool mvi_m(_8085MP *Machine);
static bool stc(_8085MP *Machine);
static bool dad_sp(_8085MP *Machine);
static bool lda(_8085MP *Machine);
static bool dcx_sp(_8085MP *Machine);
static bool inr_a(_8085MP *Machine);
static bool dcr_a(_8085MP *Machine);
static bool mvi_a(_8085MP *Machine);
static bool cmc(_8085MP *Machine);
static bool mov_b_b(_8085MP *Machine);
static bool mov_b_c(_8085MP *Machine);
static bool mov_b_d(_8085MP *Machine);
static bool mov_b_e(_8085MP *Machine);
static bool mov_b_h(_8085MP *Machine);
static bool mov_b_l(_8085MP *Machine);
static bool mov_b_m(_8085MP *Machine);
static bool mov_b_a(_8085MP *Machine);
static bool mov_c_b(_8085MP *Machine);
static bool mov_c_c(_8085MP *Machine);
static bool mov_c_d(_8085MP *Machine);
static bool mov_c_e(_8085MP *Machine);
static bool mov_c_h(_8085MP *Machine);
static bool mov_c_l(_8085MP *Machine);
static bool mov_c_m(_8085MP *Machine);
static bool mov_c_a(_8085MP *Machine);
static bool mov_d_b(_8085MP *Machine);
static bool mov_d_c(_8085MP *Machine);
static bool mov_d_d(_8085MP *Machine);
static bool mov_d_e(_8085MP *Machine);
static bool mov_d_h(_8085MP *Machine);
static bool mov_d_l(_8085MP *Machine);
static bool mov_d_m(_8085MP *Machine);
static bool mov_d_a(_8085MP *Machine);
static bool mov_e_b(_8085MP *Machine);
static bool mov_e_c(_8085MP *Machine);
static bool mov_e_d(_8085MP *Machine);
static bool mov_e_e(_8085MP *Machine);
static bool mov_e_h(_8085MP *Machine);
static bool mov_e_l(_8085MP *Machine);
static bool mov_e_m(_8085MP *Machine);
static bool mov_e_a(_8085MP *Machine);
static bool mov_h_b(_8085MP *Machine);
static bool mov_h_c(_8085MP *Machine);
static bool mov_h_d(_8085MP *Machine);
static bool mov_h_e(_8085MP *Machine);
static bool mov_h_h(_8085MP *Machine);
static bool mov_h_l(_8085MP *Machine);
static bool mov_h_m(_8085MP *Machine);
static bool mov_h_a(_8085MP *Machine);
static bool mov_l_b(_8085MP *Machine);
static bool mov_l_c(_8085MP *Machine);
static bool mov_l_d(_8085MP *Machine);
static bool mov_l_e(_8085MP *Machine);
static bool mov_l_h(_8085MP *Machine);
static bool mov_l_l(_8085MP *Machine);
static bool mov_l_m(_8085MP *Machine);
static bool mov_l_a(_8085MP *Machine);
static bool mov_m_b(_8085MP *Machine);
static bool mov_m_c(_8085MP *Machine);
static bool mov_m_d(_8085MP *Machine);
static bool mov_m_e(_8085MP *Machine);
static bool mov_m_h(_8085MP *Machine);
static bool mov_m_l(_8085MP *Machine);
static bool mov_m_a(_8085MP *Machine);
static bool mov_a_b(_8085MP *Machine);
static bool mov_a_c(_8085MP *Machine);
static bool mov_a_d(_8085MP *Machine);
static bool mov_a_e(_8085MP *Machine);
static bool mov_a_h(_8085MP *Machine);
static bool mov_a_l(_8085MP *Machine);
static bool mov_a_m(_8085MP *Machine);
static bool mov_a_a(_8085MP *Machine);
static bool add_b(_8085MP *Machine);
static bool add_c(_8085MP *Machine);
static bool add_d(_8085MP *Machine);
static bool add_e(_8085MP *Machine);
static bool add_h(_8085MP *Machine);
static bool add_l(_8085MP *Machine);
static bool add_m(_8085MP *Machine);
static bool add_a(_8085MP *Machine);
static bool adc_b(_8085MP *Machine);
static bool adc_c(_8085MP *Machine);
static bool adc_d(_8085MP *Machine);
static bool adc_e(_8085MP *Machine);
static bool adc_h(_8085MP *Machine);
static bool adc_l(_8085MP *Machine);
static bool adc_m(_8085MP *Machine);
static bool adc_a(_8085MP *Machine);
static bool sub_b(_8085MP *Machine);
static bool sub_c(_8085MP *Machine);
static bool sub_d(_8085MP *Machine);
static bool sub_e(_8085MP *Machine);
static bool sub_h(_8085MP *Machine);
static bool sub_l(_8085MP *Machine);
static bool sub_m(_8085MP *Machine);
static bool sub_a(_8085MP *Machine);
static bool sbb_b(_8085MP *Machine);
static bool sbb_c(_8085MP *Machine);
static bool sbb_d(_8085MP *Machine);
static bool sbb_e(_8085MP *Machine);
static bool sbb_h(_8085MP *Machine);
static bool sbb_l(_8085MP *Machine);
static bool sbb_m(_8085MP *Machine);
static bool sbb_a(_8085MP *Machine);
static bool ana_b(_8085MP *Machine);
static bool ana_c(_8085MP *Machine);
static bool ana_d(_8085MP *Machine);
static bool ana_e(_8085MP *Machine);
static bool ana_h(_8085MP *Machine);
static bool ana_l(_8085MP *Machine);
static bool ana_m(_8085MP *Machine);
static bool ana_a(_8085MP *Machine);
static bool xra_b(_8085MP *Machine);
static bool xra_c(_8085MP *Machine);
static bool xra_d(_8085MP *Machine);
static bool xra_e(_8085MP *Machine);
static bool xra_h(_8085MP *Machine);
static bool xra_l(_8085MP *Machine);
static bool xra_m(_8085MP *Machine);
static bool xra_a(_8085MP *Machine);
static bool ora_b(_8085MP *Machine);
static bool ora_c(_8085MP *Machine);
static bool ora_d(_8085MP *Machine);
static bool ora_e(_8085MP *Machine);
static bool ora_h(_8085MP *Machine);
static bool ora_l(_8085MP *Machine);
static bool ora_m(_8085MP *Machine);
static bool ora_a(_8085MP *Machine);
static bool cmp_b(_8085MP *Machine);
static bool cmp_c(_8085MP *Machine);
static bool cmp_d(_8085MP *Machine);
static bool cmp_e(_8085MP *Machine);
static bool cmp_h(_8085MP *Machine);
static bool cmp_l(_8085MP *Machine);
static bool cmp_m(_8085MP *Machine);
static bool cmp_a(_8085MP *Machine);
static bool rnz(_8085MP *Machine);
static bool pop_b(_8085MP *Machine);
static bool jnz(_8085MP *Machine);
static bool jmp(_8085MP *Machine);
static bool cnz(_8085MP *Machine);
static bool push_b(_8085MP *Machine);
static bool adi(_8085MP *Machine);
static bool rst_0(_8085MP *Machine);
static bool rz(_8085MP *Machine);
static bool ret(_8085MP *Machine);
static bool jz(_8085MP *Machine);
static bool cz(_8085MP *Machine);
static bool call(_8085MP *Machine);
static bool aci(_8085MP *Machine);
static bool rst_1(_8085MP *Machine);
static bool rnc(_8085MP *Machine);
static bool pop_d(_8085MP *Machine);
static bool jnc(_8085MP *Machine);
static bool out(_8085MP *Machine);
static bool cnc(_8085MP *Machine);
static bool push_d(_8085MP *Machine);
static bool sui(_8085MP *Machine);
static bool rst_2(_8085MP *Machine);
static bool rc(_8085MP *Machine);
static bool invalid(_8085MP *Machine);
static bool jc(_8085MP *Machine);
static bool in(_8085MP *Machine);
static bool cc(_8085MP *Machine);
static bool sbi(_8085MP *Machine);
static bool rst_3(_8085MP *Machine);
static bool rpo(_8085MP *Machine);
static bool pop_h(_8085MP *Machine);
static bool jpo(_8085MP *Machine);
static bool xthl(_8085MP *Machine);
static bool cpo(_8085MP *Machine);
static bool push_h(_8085MP *Machine);
static bool ani(_8085MP *Machine);
static bool rst_4(_8085MP *Machine);
static bool rpe(_8085MP *Machine);
static bool pchl(_8085MP *Machine);
static bool jpe(_8085MP *Machine);
static bool xchg(_8085MP *Machine);
static bool cpe(_8085MP *Machine);
static bool xri(_8085MP *Machine);
static bool rst_5(_8085MP *Machine);
static bool rp(_8085MP *Machine);
static bool pop_psw(_8085MP *Machine);
static bool jp(_8085MP *Machine);
static bool di(_8085MP *Machine);
static bool cp(_8085MP *Machine);
static bool push_psw(_8085MP *Machine);
static bool ori(_8085MP *Machine);
static bool rst_6(_8085MP *Machine);
static bool rm(_8085MP *Machine);
static bool sphl(_8085MP *Machine);
static bool jm(_8085MP *Machine);
static bool ei(_8085MP *Machine);
static bool cm(_8085MP *Machine);
static bool cpi(_8085MP *Machine);
static bool rst_7(_8085MP *Machine);

// All Helper Function Defined
static data getoperand(_8085MP *Machine);
static address pair_data_get(data higher, data lower);
static void pair_data_set(data *higher, data *lower, address value);
static bool pairAdder(_8085MP *Machine, data higher, data lower);
static void setArthMaticFlags(_8085MP *Machine);
static address popFromStack(_8085MP *Machine);
static bool pushToStack(_8085MP *Machine, data lower, data higher);
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
static instruction_set allInstruction[0x100] = {
    {nop}, //0x00
    {lxi_b}, //0x01
    {stax_b}, //0x02
    {inx_b}, //0x03
    {inr_b}, //0x04
    {dcr_b}, //0x05
    {mvi_b}, //0x06
    {rlc}, //0x07
    {invalid}, //0x08
    {dad_b}, //0x09
    {ldax_b}, //0x0a
    {dcx_b}, //0x0b
    {inr_c}, //0x0c
    {dcr_c}, //0x0d
    {mvi_c}, //0x0e
    {rrc}, //0x0f
    {invalid}, //0x10
    {lxi_d}, //0x11
    {stax_d}, //0x12
    {inx_d}, //0x13
    {inr_d}, //0x14
    {dcr_d}, //0x15
    {mvi_d}, //0x16
    {ral}, //0x17
    {invalid}, //0x18
    {dad_d}, //0x19
    {ldax_d}, //0x1a
    {dcx_d}, //0x1b
    {inr_e}, //0x1c 
    {dcr_e}, //0x1d
    {mvi_e}, //0x1e
    {rar}, //0x1f
    {rim}, //0x20
    {lxi_h}, //0x21 
    {shld}, //0x22
    {inx_h}, //0x23
    {inr_h}, //0x24
    {dcr_h}, //0x25
    {mvi_h}, //0x26
    {daa}, //0x27
    {invalid}, //0x28
    {dad_h}, //0x29
    {lhld}, //0x2a
    {dcx_h}, //0x2b
    {inr_l}, //0x2c
    {dcr_l}, //0x2d
    {mvi_l}, //0x2e
    {cma}, //0x2f
    {sim}, //0x30
    {lxi_sp}, //0x31
    {sta}, //0x32
    {inx_sp}, //0x33
    {inr_m}, //0x34
    {dcr_m}, //0x35
    {mvi_m}, //0x36
    {stc}, //0x37
    {invalid}, //0x38
    {dad_sp}, //0x39
    {lda}, //0x3a
    {dcx_sp}, //0x3b
    {inr_a}, //0x3c
    {dcr_a}, //0x3d
    {mvi_a}, //0x3e
    {cmc}, //0x3f
    {mov_b_b}, //0x40
    {mov_b_c}, //0x41
    {mov_b_d}, //0x42
    {mov_b_e}, //0x43
    {mov_b_h}, //0x44
    {mov_b_l}, //0x45
    {mov_b_m}, //0x46
    {mov_b_a}, //0x47
    {mov_c_b}, //0x48
    {mov_c_c}, //0x49
    {mov_c_d}, //0x4a
    {mov_c_e}, //0x4b
    {mov_c_h}, //0x4c
    {mov_c_l}, //0x4d
    {mov_c_m}, //0x4e
    {mov_c_a}, //0x4f
    {mov_d_b}, //0x50
    {mov_d_c}, //0x51
    {mov_d_d}, //0x52
    {mov_d_e}, //0x53
    {mov_d_h}, //0x54
    {mov_d_l}, //0x55
    {mov_d_m}, //0x56
    {mov_d_a}, //0x57
    {mov_e_b}, //0x58
    {mov_e_c}, //0x59
    {mov_e_d}, //0x5a
    {mov_e_e}, //0x5b
    {mov_e_h}, //0x5c
    {mov_e_l}, //0x5d
    {mov_e_m}, //0x5e
    {mov_e_a}, //0x5f
    {mov_h_b}, //0x60
    {mov_h_c}, //0x61
    {mov_h_d}, //0x62
    {mov_h_e}, //0x63
    {mov_h_h}, //0x64
    {mov_h_l}, //0x65
    {mov_h_m}, //0x66
    {mov_h_a}, //0x67
    {mov_l_b}, //0x68
    {mov_l_c}, //0x69
    {mov_l_d}, //0x6a
    {mov_l_e}, //0x6b
    {mov_l_h}, //0x6c
    {mov_l_l}, //0x6d
    {mov_l_m}, //0x6e
    {mov_l_a}, //0x6f
    {mov_m_b}, //0x70
    {mov_m_c}, //0x71
    {mov_m_d}, //0x72
    {mov_m_e}, //0x73
    {mov_m_h}, //0x74
    {mov_m_l}, //0x75
    {hlt}, //0x76
    {mov_m_a}, //0x77
    {mov_a_b}, //0x78
    {mov_a_c}, //0x79
    {mov_a_d}, //0x7a
    {mov_a_e}, //0x7b
    {mov_a_h}, //0x7c
    {mov_a_l}, //0x7d
    {mov_a_m}, //0x7e
    {mov_a_a}, //0x7f
    {add_b}, //0x80
    {add_c}, //0x81
    {add_d}, //0x82
    {add_e}, //0x83
    {add_h}, //0x84
    {add_l}, //0x85
    {add_m}, //0x86
    {add_a}, //0x87
    {adc_b}, //0x88
    {adc_c}, //0x89
    {adc_d}, //0x8a
    {adc_e}, //0x8b
    {adc_h}, //0x8c
    {adc_l}, //0x8d
    {adc_m}, //0x8e
    {adc_a}, //0x8f
    {sub_b}, //0x90
    {sub_c}, //0x91
    {sub_d}, //0x92
    {sub_e}, //0x93
    {sub_h}, //0x94
    {sub_l}, //0x95
    {sub_m}, //0x96
    {sub_a}, //0x97
    {sbb_b}, //0x98
    {sbb_c}, //0x99
    {sbb_d}, //0x9a
    {sbb_e}, //0x9b
    {sbb_h}, //0x9c
    {sbb_l}, //0x9d
    {sbb_m}, //0x9e
    {sbb_a}, //0x9f
    {ana_b}, //0xa0
    {ana_c}, //0xa1
    {ana_d}, //0xa2
    {ana_e}, //0xa3
    {ana_h}, //0xa4
    {ana_l}, //0xa5
    {ana_m}, //0xa6
    {ana_a}, //0xa7
    {xra_b}, //0xa8
    {xra_c}, //0xa9
    {xra_d}, //0xaa
    {xra_e}, //0xab
    {xra_h}, //0xac
    {xra_l}, //0xad
    {xra_m}, //0xae
    {xra_a}, //0xaf
    {ora_b}, //0xb0
    {ora_c}, //0xb1
    {ora_d}, //0xb2
    {ora_e}, //0xb3
    {ora_h}, //0xb4
    {ora_l}, //0xb5
    {ora_m}, //0xb6
    {ora_a}, //0xb7
    {cmp_b}, //0xb8
    {cmp_c}, //0xb9
    {cmp_d}, //0xba
    {cmp_e}, //0xbb
    {cmp_h}, //0xbc
    {cmp_l}, //0xbd
    {cmp_m}, //0xbe
    {cmp_a}, //0xbf
    {rnz}, //0xc0
    {pop_b}, //0xc1
    {jnz}, //0xc2
    {jmp},
    {cnz}, //0xc4
    {push_b}, //0xc5
    {adi}, //0xc6
    {rst_0}, //0xc7
    {rz}, //0xc8
    {ret}, //0xc9
    {jz}, //0xca
    {invalid}, //0xcb
    {cz}, //0xcc
    {call}, //0xcd
    {aci}, //0xce
    {rst_1}, //0xcf
    {rnc}, //0xd0
    {pop_d}, //0xd1
    {jnc}, //0xd2
    {out}, //0xd3
    {cnc}, //0xd4
    {push_d}, //0xd5
    {sui}, //0xd6
    {rst_2}, //0xd7
    {rc}, //0xd8
    {invalid}, //0xd9
    {jc}, //0xda
    {in}, //0xdb
    {cc}, //0xdc
    {invalid}, //0xdd
    {sbi}, //0xde
    {rst_3}, //0xdf
    {rpo}, //0xe0
    {pop_h}, //0xe1
    {jpo}, //0xe2
    {xthl}, //0xe3
    {cpo}, //0xe4
    {push_h}, //0xe5
    {ani}, //0xe6
    {rst_4}, //0xe7
    {rpe}, //0xe8
    {pchl}, //0xe9
    {jpe}, //0xea
    {xchg}, //0xeb
    {cpe}, //0xec
    {invalid}, //0xed
    {xri}, //0xee
    {rst_5}, //0xef
    {rp}, //0xf0
    {pop_psw}, //0xf1
    {jp}, //0xf2
    {di}, //0xf3
    {cp}, //0xf4
    {push_psw}, //0xf5
    {ori}, //0xf6
    {rst_6}, //0xf7
    {rm}, //0xf8
    {sphl}, //0xf9
    {jm}, //0xfa
    {ei}, //0xfb
    {cm}, //0xfc
    {invalid}, //0xfd
    {cpi}, //0xfe
    {rst_7} //0xff

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
    Machine->memory[pair_data_get(Machine->b, Machine->c)] = Machine->a;
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
    pair_data_set(&Machine->b, &Machine->c, pair_data_get(Machine->b, Machine->c) + 0x01);
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
    Machine->a = Machine->memory[pair_data_get(Machine->b, Machine->c)];
    return true;
}
static bool dcx_b(_8085MP *Machine){
    // Does Not Affect Any Flag
    pair_data_set(&Machine->b, &Machine->c, pair_data_get(Machine->b, Machine->c) - 0x01);
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
    Machine->memory[pair_data_get(Machine->d, Machine->e)] = Machine->a;
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
    pair_data_set(&Machine->b, &Machine->c, pair_data_get(Machine->d, Machine->e) + 0x01);
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
    Machine->a = Machine->memory[pair_data_get(Machine->d, Machine->e)];
    return true;
}
static bool dcx_d(_8085MP *Machine){
    // Does Not Affect Any Flag
    pair_data_set(&Machine->d, &Machine->e, pair_data_get(Machine->d, Machine->e) - 0x01);
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
    pair_data_set(&Machine->h, &Machine->l, pair_data_get(Machine->h, Machine->l) + 0x01);
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
    pair_data_set(&Machine->h, &Machine->l, pair_data_get(Machine->h, Machine->l) - 0x01);
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
static bool sta(_8085MP *Machine){
    Machine->memory[pair_data_get(getoperand(Machine), getoperand(Machine))] = Machine->a; 
    return true;
}
static bool inx_sp(_8085MP *Machine){
    Machine->sp = Machine->sp + 0x01;
    return true;
}
static bool inr_m(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->h, Machine->l)]++;
    return true;
}

static bool dcr_m(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->h, Machine->l)]--;
    return true;
}
static bool mvi_m(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->h, Machine->l)] = getoperand(Machine);
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
    Machine->b = Machine->memory[pair_data_get(Machine->h, Machine->l)];
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
    Machine->c = Machine->memory[pair_data_get(Machine->h, Machine->l)];
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
    Machine->d = Machine->memory[pair_data_get(Machine->h, Machine->l)];
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
    Machine->e = Machine->memory[pair_data_get(Machine->h, Machine->l)];
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
    Machine->h = Machine->memory[pair_data_get(Machine->h, Machine->l)];
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
    Machine->l = Machine->memory[pair_data_get(Machine->h, Machine->l)];
    return true;
}
static bool mov_l_a(_8085MP *Machine){
    Machine->l = Machine->a;
    return true;
}
static bool mov_m_b(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->h, Machine->l)] = Machine->b;
    return true;
}
static bool mov_m_c(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->h, Machine->l)] = Machine->c;
    return true;
}
static bool mov_m_d(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->h, Machine->l)] = Machine->d;
    return true;
}
static bool mov_m_e(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->h, Machine->l)] = Machine->e;
    return true;
}
static bool mov_m_h(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->h, Machine->l)] = Machine->h;
    return true;
}
static bool mov_m_l(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->h, Machine->l)] = Machine->l;
    return true;
}
// HLT
static bool mov_m_a(_8085MP *Machine){
    Machine->memory[pair_data_get(Machine->h, Machine->l)] = Machine->a;
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
    Machine->a = Machine->memory[pair_data_get(Machine->h, Machine->l)];
    return true;
}
static bool mov_a_a(_8085MP *Machine){
    Machine->a = Machine->a;
    return true;
}
static bool add_b(_8085MP *Machine){
    ALU(Machine, Machine->b, true, NULL);
    return true;
}
static bool add_c(_8085MP *Machine){
    ALU(Machine, Machine->c, true, NULL);
    return true;
}
static bool add_d(_8085MP *Machine){
    ALU(Machine, Machine->d, true, NULL);
    return true;
}
static bool add_e(_8085MP *Machine){
    ALU(Machine, Machine->e, true, NULL);
    return true;
}
static bool add_h(_8085MP *Machine){
    ALU(Machine, Machine->h, true, NULL);
    return true;
}
static bool add_l(_8085MP *Machine){
    ALU(Machine, Machine->l, true, NULL);
    return true;
}
static bool add_m(_8085MP *Machine){
    ALU(Machine, Machine->memory[pair_data_get(Machine->h, Machine->l)], true, NULL);
    return true;
}
static bool add_a(_8085MP *Machine){
    ALU(Machine, Machine->a, true, NULL);
    return true;
}
static bool adc_b(_8085MP *Machine){
    ALU(Machine, Machine->b, true, NULL);
    ALU(Machine, getCarry(Machine), true, NULL);
    return true;
}
static bool adc_c(_8085MP *Machine){
    ALU(Machine, Machine->c, true, NULL);
    ALU(Machine, getCarry(Machine), true, NULL);
    return true;
}
static bool adc_d(_8085MP *Machine){
    ALU(Machine, Machine->e, true, NULL);
    ALU(Machine, getCarry(Machine), true, NULL);
    return true;
}
static bool adc_e(_8085MP *Machine){
    ALU(Machine, Machine->e, true, NULL);
    ALU(Machine, getCarry(Machine), true, NULL);
    return true;
}
static bool adc_h(_8085MP *Machine){
    ALU(Machine, Machine->h, true, NULL);
    ALU(Machine, getCarry(Machine), true, NULL);
    return true;
}
static bool adc_l(_8085MP *Machine){
    ALU(Machine, Machine->l, true, NULL);
    ALU(Machine, getCarry(Machine), true, NULL);
    return true;
}
static bool adc_m(_8085MP *Machine){
    ALU(Machine, Machine->memory[pair_data_get(Machine->h, Machine->l)] ,true, NULL);
    ALU(Machine, getCarry(Machine), true, NULL);
    return true;
}
static bool adc_a(_8085MP *Machine){
    ALU(Machine, Machine->memory[pair_data_get(Machine->h, Machine->l)], true, NULL);
    ALU(Machine, getCarry(Machine), true, NULL);
    return true;
}
static bool sub_b(_8085MP *Machine){
    ALU(Machine, Machine->b, false, NULL);
    return true;
}
static bool sub_c(_8085MP *Machine){
    ALU(Machine, Machine->c, false, NULL);
    return true;
}
static bool sub_d(_8085MP *Machine){
    ALU(Machine, Machine->d, false, NULL);
    return true;
}
static bool sub_e(_8085MP *Machine){
    ALU(Machine, Machine->e, false, NULL);
    return true;
}
static bool sub_h(_8085MP *Machine){
    ALU(Machine, Machine->h, false, NULL);
    return true;
}
static bool sub_l(_8085MP *Machine){
    ALU(Machine, Machine->l, false, NULL);
    return true;
}
static bool sub_m(_8085MP *Machine){
    ALU(Machine, Machine->memory[pair_data_get(Machine->h, Machine->l)], false, NULL);
    return true;
}
static bool sub_a(_8085MP *Machine){
    ALU(Machine, Machine->a, false, NULL);
    return true;
}
static bool sbb_b(_8085MP *Machine){
    ALU(Machine, Machine->b, false, NULL);
    ALU(Machine, getCarry(Machine), false, NULL);
    return true;
}
static bool sbb_c(_8085MP *Machine){
    ALU(Machine, Machine->c, false, NULL);
    ALU(Machine, getCarry(Machine), false, NULL);
    return true;
}
static bool sbb_d(_8085MP *Machine){
    ALU(Machine, Machine->e, false, NULL);
    ALU(Machine, getCarry(Machine), false, NULL);
    return true;
}
static bool sbb_e(_8085MP *Machine){
    ALU(Machine, Machine->e, false, NULL);
    ALU(Machine, getCarry(Machine), false, NULL);
    return true;
}
static bool sbb_h(_8085MP *Machine){
    ALU(Machine, Machine->h, false, NULL);
    ALU(Machine, getCarry(Machine), false, NULL);
    return true;
}
static bool sbb_l(_8085MP *Machine){
    ALU(Machine, Machine->l, false, NULL);
    ALU(Machine, getCarry(Machine), false, NULL);
    return true;
}
static bool sbb_m(_8085MP *Machine){
    ALU(Machine, Machine->memory[pair_data_get(Machine->h, Machine->l)] ,false, NULL);
    ALU(Machine, getCarry(Machine), false, NULL);
    return true;
}
static bool sbb_a(_8085MP *Machine){
    ALU(Machine, Machine->memory[pair_data_get(Machine->h, Machine->l)], false, NULL);
    ALU(Machine, getCarry(Machine), false, NULL);
    return true;
}
static bool ana_b(_8085MP *Machine){
    Machine->a &= Machine->b;
    resetCarry(Machine);
    setAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool ana_c(_8085MP *Machine){
    Machine->a &= Machine->c;
    resetCarry(Machine);
}
static bool ana_d(_8085MP *Machine){
    Machine->a &= Machine->d;
    resetCarry(Machine);
    setAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool ana_e(_8085MP *Machine){
    Machine->a &= Machine->e;
    resetCarry(Machine);
    setAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool ana_h(_8085MP *Machine){
    Machine->a &= Machine->h;
    resetCarry(Machine);
    setAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool ana_l(_8085MP *Machine){
    Machine->a &= Machine->l;
    resetCarry(Machine);
    setAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool ana_m(_8085MP *Machine){
    Machine->a &= Machine->memory[pair_data_get(Machine->h, Machine->l)];
    resetCarry(Machine);
    setAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool ana_a(_8085MP *Machine){
    Machine->a &= Machine->a;
    resetCarry(Machine);
    setAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool xra_b(_8085MP *Machine){
    Machine->a ^= Machine->b;
    resetCarry(Machine);
    resetAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool xra_c(_8085MP *Machine){
    Machine->a ^= Machine->c;
    resetCarry(Machine);
}
static bool xra_d(_8085MP *Machine){
    Machine->a ^= Machine->d;
    resetCarry(Machine);
    resetAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool xra_e(_8085MP *Machine){
    Machine->a ^= Machine->e;
    resetCarry(Machine);
    resetAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool xra_h(_8085MP *Machine){
    Machine->a ^= Machine->h;
    resetCarry(Machine);
    resetAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool xra_l(_8085MP *Machine){
    Machine->a ^= Machine->l;
    resetCarry(Machine);
    resetAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool xra_m(_8085MP *Machine){
    Machine->a ^= Machine->memory[pair_data_get(Machine->h, Machine->l)];
    resetCarry(Machine);
    resetAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool xra_a(_8085MP *Machine){
    Machine->a ^= Machine->a;
    resetCarry(Machine);
    resetAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool ora_b(_8085MP *Machine){
    Machine->a |= Machine->b;
    resetCarry(Machine);
    resetAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool ora_c(_8085MP *Machine){
    Machine->a |= Machine->c;
    resetCarry(Machine);
}
static bool ora_d(_8085MP *Machine){
    Machine->a |= Machine->d;
    resetCarry(Machine);
    resetAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool ora_e(_8085MP *Machine){
    Machine->a |= Machine->e;
    resetCarry(Machine);
    resetAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool ora_h(_8085MP *Machine){
    Machine->a |= Machine->h;
    resetCarry(Machine);
    resetAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool ora_l(_8085MP *Machine){
    Machine->a |= Machine->l;
    resetCarry(Machine);
    resetAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool ora_m(_8085MP *Machine){
    Machine->a |= Machine->memory[pair_data_get(Machine->h, Machine->l)];
    resetCarry(Machine);
    resetAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool ora_a(_8085MP *Machine){
    Machine->a |= Machine->a;
    resetCarry(Machine);
    resetAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool cmp_b(_8085MP *Machine){
    data tempA = Machine->a;
    ALU(Machine, Machine->b, false, NULL);
    Machine->a = tempA;
    return true;
}
static bool cmp_c(_8085MP *Machine){
    data tempA = Machine->a;
    ALU(Machine, Machine->c, false, NULL);
    Machine->a = tempA;
    return true;
}
static bool cmp_d(_8085MP *Machine){
    data tempA = Machine->a;
    ALU(Machine, Machine->d, false, NULL);
    Machine->a = tempA;
    return true;
}
static bool cmp_e(_8085MP *Machine){
    data tempA = Machine->a;
    ALU(Machine, Machine->e, false, NULL);
    Machine->a = tempA;
    return true;
}
static bool cmp_h(_8085MP *Machine){
    data tempA = Machine->a;
    ALU(Machine, Machine->h, false, NULL);
    Machine->a = tempA;
    return true;
}
static bool cmp_l(_8085MP *Machine){
    data tempA = Machine->a;
    ALU(Machine, Machine->l, false, NULL);
    Machine->a = tempA;
    return true;
}
static bool cmp_m(_8085MP *Machine){
    data tempA = Machine->a;
    ALU(Machine, Machine->memory[pair_data_get(Machine->h, Machine->l)], false, NULL);
    Machine->a = tempA;
    return true;
}
static bool cmp_a(_8085MP *Machine){
    data tempA = Machine->a;
    ALU(Machine, Machine->a, false, NULL);
    Machine->a = tempA;
    return true;
}
// SubRoutine
static bool rnz(_8085MP *Machine){
    if(!getZero(Machine)){
        Machine->pc = popFromStack(Machine);
    }
    return true;
}
static bool pop_b(_8085MP *Machine){
    Machine->b = popFromStack(Machine);
    return true;
}
static bool jnz(_8085MP *Machine){
    if(!getZero(Machine)){
        Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
    }
    return true;
}

static bool jmp(_8085MP *Machine){
    Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
    return true;
}
static bool cnz(_8085MP *Machine){
    if(!getZero(Machine)){
        address currentPC = Machine->pc + 0x02;
        Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
        pushToStack(Machine, currentPC, currentPC >> 8 );
    }
    return true;
}
static bool push_b(_8085MP *Machine){
    pushToStack(Machine, Machine->c, Machine->b);
    return true;
}
static bool adi(_8085MP *Machine){
    ALU(Machine, getoperand(Machine), true, NULL);
    return true;
}
// RST 0 SOFTWARE INTERUPT
static bool rst_0(_8085MP *Machine){
    Machine->pc = 0; // Easily Convert RST 
    return true;
}
static bool rz(_8085MP *Machine){
    if(getZero(Machine)){
        Machine->pc = popFromStack(Machine);
    }
    return true;
}
static bool ret(_8085MP *Machine){
    Machine->pc = popFromStack(Machine);
    return true;
}

static bool jz(_8085MP *Machine){
    if(getZero(Machine)){
        Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
    }
    return true;
}
static bool cz(_8085MP *Machine){
    if(getZero(Machine)){
        address currentPC = Machine->pc + 0x02;
        Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
        pushToStack(Machine, currentPC, currentPC >> 8 );
    }
    return true;
}
static bool call(_8085MP *Machine){
    address currentPC = Machine->pc + 0x02;
    Machine->pc = pair_data_get(getoperand(Machine),getoperand(Machine));
    pushToStack(Machine, currentPC, currentPC << 8 );
    return true;
}

static bool aci(_8085MP *Machine){
    ALU(Machine, getoperand(Machine), true, NULL);
    ALU(Machine, 0x01, true, NULL);    
    return true;
}
static bool rst_1(_8085MP *Machine){
    Machine->pc = 8; // Easily Convert RST 
    return true;
}

static bool rnc(_8085MP *Machine){
    if(!getCarry(Machine)){
        Machine->pc = popFromStack(Machine);
    }
    return true;
}
static bool pop_d(_8085MP *Machine){
    Machine->d = popFromStack(Machine);
    return true;
}
static bool jnc(_8085MP *Machine){
    if(!getCarry(Machine)){
        Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
    }
    return true;
}
// Out -> Next Update -> Still process it
static bool out(_8085MP *Machine){
    getoperand(Machine);
    // Port Address :_
}
static bool cnc(_8085MP *Machine){
    if(!getCarry(Machine)){
        address currentPC = Machine->pc + 0x02;
        Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
        pushToStack(Machine, currentPC, currentPC >> 8 );
    }
    return true;
}
static bool push_d(_8085MP *Machine){
    pushToStack(Machine, Machine->e, Machine->d);
    return true;
}
static bool sui(_8085MP *Machine){
    ALU(Machine, getoperand(Machine), false, NULL);
    ALU(Machine, 0x01, false, NULL);    
    return true;
}
static bool rst_2(_8085MP *Machine){
    Machine->pc = 16; // Easily Convert RST 
    return true;
}
static bool rc(_8085MP *Machine){
    if(getCarry(Machine)){
        Machine->pc = popFromStack(Machine);
    }
    return true;
}
static bool jc(_8085MP *Machine){
    if(getCarry(Machine)){
        Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
    }
    return true;
}
static bool in(_8085MP *Machine){
    getoperand(Machine);
    // Port Address :_
}
static bool cc(_8085MP *Machine){
    if(getCarry(Machine)){
        address currentPC = Machine->pc + 0x02;
        Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
        pushToStack(Machine, currentPC, currentPC >> 8 );
    }
    return true;
}
static bool sbi(_8085MP *Machine){
    ALU(Machine, getoperand(Machine), false, NULL);
    return true;
}
static bool rst_3(_8085MP *Machine){
    Machine->pc = 24; // Easily Convert RST 
    return true;
}
static bool rpo(_8085MP *Machine){
    if(!getParity(Machine)){
        Machine->pc = popFromStack(Machine);
    }
    return true;
}
static bool pop_h(_8085MP *Machine){
    Machine->h = popFromStack(Machine);
    return true;
}
static bool jpo(_8085MP *Machine){
    if(!getParity(Machine)){
        Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
    }
    return true;
}
static bool xthl(_8085MP *Machine){
    Machine->memory[Machine->sp] = Machine->l;
    Machine->memory[Machine->sp+0x01] = Machine->h;
    return true;
}
static bool cpo(_8085MP *Machine){
    if(!getParity(Machine)){
        address currentPC = Machine->pc + 0x02;
        Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
        pushToStack(Machine, currentPC, currentPC >> 8 );
    }
    return true;
}
static bool push_h(_8085MP *Machine){
    pushToStack(Machine, Machine->l, Machine->h);
    return true;
}
static bool ani(_8085MP *Machine){
    Machine->a &= getoperand(Machine);
    resetCarry(Machine);
    setAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool rst_4(_8085MP *Machine){
    Machine->pc = 32; // Easily Convert RST 
    return true;
}
static bool rpe(_8085MP *Machine){
    if(getParity(Machine)){
        Machine->pc = popFromStack(Machine);
    }
    return true;
}
static bool pchl(_8085MP *Machine){
    Machine->pc = pair_data_get(Machine->h, Machine->l);
    return true;
}
static bool jpe(_8085MP *Machine){
    if(getParity(Machine)){
        Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
    }
    return true;
}
static bool xchg(_8085MP *Machine){
    data tempLower =  Machine->h;
    Machine->h = Machine->d;
    Machine->d = tempLower;
    tempLower = Machine->l;
    Machine->l = Machine->e;
    Machine->e = tempLower;
    return true;
}
static bool cpe(_8085MP *Machine){
    if(getParity(Machine)){
        address currentPC = Machine->pc + 0x02;
        Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
        pushToStack(Machine, currentPC, currentPC >> 8 );
    }
    return true;
}
static bool xri(_8085MP *Machine){
    Machine->a ^= getoperand(Machine);
    resetCarry(Machine);
    resetAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool rst_5(_8085MP *Machine){
    Machine->pc = 40; // Easily Convert RST 
    return true;
}
static bool rp(_8085MP *Machine){
    if(!getSign(Machine)){
        Machine->pc = popFromStack(Machine);
    }
    return true;
}
static bool pop_psw(_8085MP *Machine){
    address temp = popFromStack(Machine);
    Machine->a = temp >> 8;
    Machine->flag = temp;
    return true;
}
static bool jp(_8085MP *Machine){
    if(!getSign(Machine)){
        Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
    }
    return true;
}
// DI Next Update
static bool di(_8085MP *Machine){
    return true;
}
static bool cp(_8085MP *Machine){
    if(!getSign(Machine)){
        address currentPC = Machine->pc + 0x02;
        Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
        pushToStack(Machine, currentPC, currentPC >> 8 );
    }
    return true;
}
static bool push_psw(_8085MP *Machine){
    pushToStack(Machine, Machine->flag, Machine->a);
    return true;
}
static bool ori(_8085MP *Machine){
    Machine->a |= getoperand(Machine);
    resetCarry(Machine);
    resetAC(Machine);
    setArthMaticFlags(Machine);
    return true;
}
static bool rst_6(_8085MP *Machine){
    Machine->pc = 48; // Easily Convert RST 
    return true;
}
static bool rm(_8085MP *Machine){
    if(getSign(Machine)){
        Machine->pc = popFromStack(Machine);
    }
    return true;
}
static bool sphl(_8085MP *Machine){
    Machine->sp = pair_data_get(Machine->h, Machine->l);
    return true;
}
static bool jm(_8085MP *Machine){
    if(getSign(Machine)){
        Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
    }
    return true;
}
// EI NEXT UPDATE
static bool ei(_8085MP *Machine){
    return true;
}
static bool cm(_8085MP *Machine){
    if(getSign(Machine)){
        address currentPC = Machine->pc + 0x02;
        Machine->pc = pair_data_get(getoperand(Machine), getoperand(Machine));
        pushToStack(Machine, currentPC, currentPC >> 8 );
    }
    return true;
}
static bool cpi(_8085MP *Machine){
    data tempA = Machine->a;
    ALU(Machine, getoperand(Machine), false, NULL);
    Machine->a = tempA;
    return true;
}
static bool rst_7(_8085MP *Machine){
    Machine->pc = 56; // Easily Convert RST 
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
    Machine->pc = start + 0x01;
    Machine->sp = 0x00ff;
}
static data getoperand(_8085MP *Machine){
    return Machine->memory[Machine->pc++];
}
static address pair_data_get(data higher, data lower){
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

static void setArthMaticFlags(_8085MP *Machine){
    if(!Machine->a){
        setZero(Machine);
        setParity(Machine);
        return;
    }
    resetZero(Machine);
    if(Machine->a & 0x80)
        setSign(Machine);
    else
        resetSign(Machine);
    data parity = 0xff;
    for (int j = 0;  j < 8;  ++j){
        if(0 != (Machine->a & (1 << j)))
            parity = ~parity;
    }
    if(parity)
        setParity(Machine);
    else
        resetParity(Machine);
}

static address popFromStack(_8085MP *Machine){
    address poppedElem = pair_data_get(Machine->memory[Machine->sp-1], Machine->memory[Machine->sp]);
    Machine->sp -= 0x02;
    return poppedElem;
}
static bool pushToStack(_8085MP *Machine, data lower, data higher){
    Machine->memory[++Machine->sp]  = higher;
    Machine->memory[++Machine->sp]  = lower;
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
    // newMachine->memory[0xffff];
    return newMachine;
}

bool execute(_8085MP *machine, address start_address){
    starttup(machine, start_address);
    bool ranSuccessfully = false;
    do{ 
        
        ranSuccessfully = allInstruction[machine->memory[machine->instruction_register]].func(machine);
        machine->instruction_register = machine->pc++;
    }while(ranSuccessfully);
}
int main(){
    _8085MP *newMachine = createNewMachine();
    
    
    newMachine->memory[0x0000]=0x3E;
    newMachine->memory[0x0001]=0xff;
    newMachine->memory[0x0002]=0x3D;
    newMachine->memory[0x0003]=0xC2;
    newMachine->memory[0x0004]=0x02;
    newMachine->memory[0x0005]=0x00;
    newMachine->memory[0x0006]=0x76;
    execute(newMachine, 0x0000);
    printf("%x", newMachine->a);
    return 0;
}
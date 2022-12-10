{ 
  /* store the type of opnd , ie the addressing mode also, to help the assembler */
/* function  , asm_str , opnd1, opnd2, upper_nibble=1st operand size, lower_nibble=2nd operand size */
  {nop       , "nop"   ,  ""  , ""   , 0x00}, //0x00
  {_lxi_b    , "lxi"   ,  "b" , " "  , 0x02}, //0x01
  {stax_b    , "stax"  ,  "b" , ""   , 0x00}, //0x02
  {inx_b     , "inx"   ,  "b" , ""   , 0x00}, //0x03
  {inr_b     , "inr"   ,  "b" , ""   , 0x00}, //0x04
  {dcr_b     , "dcr"   ,  "b" , ""   , 0x00}, //0x05
  {_mvi_b    , "mvi"   ,  "b" , " "  , 0x01}, //0x06
  {rlc       , "rlc"   ,  ""  , ""   , 0x00}, //0x07
  {_invalid  , ""      ,  "x" , "x"  , 0xff}, //0x08
  {dad_b     , "dad"   ,  "b" , ""   , 0x00}, //0x09
  {ldax_b    , "ldax"  ,  "b" , ""   , 0x00}, //0x0a
  {dcx_b     , "dcx"   ,  "b" , ""   , 0x00}, //0x0b
  {inr_c     , "inr"   ,  "c" , ""   , 0x00}, //0x0c
  {dcr_c     , "dcr"   ,  "c" , ""   , 0x00}, //0x0d
  {_mvi_c    , "mvi"   ,  "c" , " "  , 0x01}, //0x0e
  {rrc       , "rrc"   ,  ""  , ""   , 0x00}, //0x0f
  {_invalid  , ""      ,  "x" , "x"  , 0xff}, //0x10
  {_lxi_d    , "lxi"   , "d"  , " "  , 0x02}, //0x11
  {stax_d    , "stax"  , "d"  , ""   , 0x00}, //0x12
  {inx_d     , "inx"   , "d"  , ""   , 0x00}, //0x13
  {inr_d     , "inr"   , "d"  , ""   , 0x00}, //0x14
  {dcr_d     , "dcr"   , "d"  , ""   , 0x00}, //0x15
  {_mvi_d    , "mvi"   , "d"  , " "  , 0x01}, //0x16
  {ral       , "ral"   , ""   , ""   , 0x00}, //0x17
  {_invalid  , ""      , "x"  , "x"  , 0xff}, //0x18
  {dad_d     , "dad"   , "d"  , ""   , 0x00}, //0x19
  {ldax_d    , "ldax"  , "d"  , ""   , 0x00}, //0x1a
  {dcx_d     , "dcx"   , "d"  , ""   , 0x00}, //0x1b
  {inr_e     , "inr"   , "e"  , ""   , 0x00}, //0x1c 
  {dcr_e     , "dcr"   , "e"  , ""   , 0x00}, //0x1d
  {_mvi_e    , "mvi"   , "e"  , " "  , 0x01}, //0x1e
  {rar       , "rar"   , ""   , ""   , 0x00}, //0x1f
  {rim       , "rim"   , ""   , ""   , 0x00}, //0x20
  {_lxi_h    , "lxi"   , "h"  , " "  , 0x02}, //0x21 
  {_shld     , "shld"  , ""   , " "  , 0x20}, //0x22
  {inx_h     , "inx"   , "h"  , ""   , 0x00}, //0x23
  {inr_h     , "inr"   , "h"  , ""   , 0x00}, //0x24
  {dcr_h     , "dcr"   , "h"  , ""   , 0x00}, //0x25
  {_mvi_h    , "mvi"   , "h"  , " "  , 0x01}, //0x26
  {daa       , "daa"   , ""   , ""   , 0x00}, //0x27
  {_invalid  , ""      , "x"  , "x"  , 0xff}, //0x28
  {dad_h     , "dad"   , "h"  , ""   , 0x00}, //0x29
  {_lhld     , "lhld"  , ""   , " "  , 0x20}, //0x2a
  {dcx_h     , "dcx"   , "h"  , ""   , 0x00}, //0x2b
  {inr_l     , "inr"   , "l"  , ""   , 0x00}, //0x2c
  {dcr_l     , "dcr"   , "l"  , ""   , 0x00}, //0x2d
  {_mvi_l    , "mvi"   , "l"  , " "  , 0x01}, //0x2e
  {cma       , "cma"   , ""   , ""   , 0x00}, //0x2f
  {sim       , "sim"   , ""   , ""   , 0x00}, //0x30
  {_lxi_sp   , "lxi"   , "sp" , " "  , 0x02}, //0x31
  {_sta      , "sta"   , ""   , " "  , 0x20}, //0x32
  {inx_sp    , "inx"   , "sp" , ""   , 0x00}, //0x33
  {inr_m     , "inr"   , "m"  , ""   , 0x00}, //0x34
  {dcr_m     , "dcr"   , "m"  , ""   , 0x00}, //0x35
  {_mvi_m    , "mvi"   , "m"  , " "  , 0x01}, //0x36
  {stc       , "stc"   , ""   , ""   , 0x00}, //0x37
  {_invalid  , ""      , "x"  , "x"  , 0xff}, //0x38
  {dad_sp    , "dad"   , "sp" , ""   , 0x00}, //0x39
  {_lda      , "lda"   , " "  , ""   , 0x20}, //0x3a
  {dcx_sp    , "dcx"   , "sp" , ""   , 0x00}, //0x3b
  {inr_a     , "inr"   , "a"  , ""   , 0x00}, //0x3c
  {dcr_a     , "dcr"   , "a"  , ""   , 0x00}, //0x3d
  {_mvi_a    , "mvi"   , "a"  , " "  , 0x01}, //0x3e
  {cmc       , "cmc"   , ""   , ""   , 0x00}, //0x3f
  {mov_b_b   , "mov"   , "b"  , "b"  , 0x00}, //0x40
  {mov_b_c   , "mov"   , "b"  , "c"  , 0x00}, //0x41
  {mov_b_d   , "mov"   , "b"  , "d"  , 0x00}, //0x42
  {mov_b_e   , "mov"   , "b"  , "e"  , 0x00}, //0x43
  {mov_b_h   , "mov"   , "b"  , "h"  , 0x00}, //0x44
  {mov_b_l   , "mov"   , "b"  , "l"  , 0x00}, //0x45
  {mov_b_m   , "mov"   , "b"  , "m"  , 0x00}, //0x46
  {mov_b_a   , "mov"   , "b"  , "a"  , 0x00}, //0x47
  {mov_c_b   , "mov"   , "c"  , "b"  , 0x00}, //0x48
  {mov_c_c   , "mov"   , "c"  , "c"  , 0x00}, //0x49
  {mov_c_d   , "mov"   , "c"  , "d"  , 0x00}, //0x4a
  {mov_c_e   , "mov"   , "c"  , "e"  , 0x00}, //0x4b
  {mov_c_h   , "mov"   , "c"  , "h"  , 0x00}, //0x4c
  {mov_c_l   , "mov"   , "c"  , "l"  , 0x00}, //0x4d
  {mov_c_m   , "mov"   , "c"  , "m"  , 0x00}, //0x4e
  {mov_c_a   , "mov"   , "c"  , "a"  , 0x00}, //0x4f
  {mov_d_b   , "mov"   , "d"  , "b"  , 0x00}, //0x50
  {mov_d_c   , "mov"   , "d"  , "c"  , 0x00}, //0x51
  {mov_d_d   , "mov"   , "d"  , "d"  , 0x00}, //0x52
  {mov_d_e   , "mov"   , "d"  , "e"  , 0x00}, //0x53
  {mov_d_h   , "mov"   , "d"  , "h"  , 0x00}, //0x54
  {mov_d_l   , "mov"   , "d"  , "l"  , 0x00}, //0x55
  {mov_d_m   , "mov"   , "d"  , "m"  , 0x00}, //0x56
  {mov_d_a   , "mov"   , "d"  , "a"  , 0x00}, //0x57
  {mov_e_b   , "mov"   , "e"  , "b"  , 0x00}, //0x58
  {mov_e_c   , "mov"   , "e"  , "c"  , 0x00}, //0x59
  {mov_e_d   , "mov"   , "e"  , "d"  , 0x00}, //0x5a
  {mov_e_e   , "mov"   , "e"  , "e"  , 0x00}, //0x5b
  {mov_e_h   , "mov"   , "e"  , "h"  , 0x00}, //0x5c
  {mov_e_l   , "mov"   , "e"  , "l"  , 0x00}, //0x5d
  {mov_e_m   , "mov"   , "e"  , "m"  , 0x00}, //0x5e
  {mov_e_a   , "mov"   , "e"  , "a"  , 0x00}, //0x5f
  {mov_h_b   , "mov"   , "h"  , "b"  , 0x00}, //0x60
  {mov_h_c   , "mov"   , "h"  , "c"  , 0x00}, //0x61
  {mov_h_d   , "mov"   , "h"  , "d"  , 0x00}, //0x62
  {mov_h_e   , "mov"   , "h"  , "e"  , 0x00}, //0x63
  {mov_h_h   , "mov"   , "h"  , "h"  , 0x00}, //0x64
  {mov_h_l   , "mov"   , "h"  , "l"  , 0x00}, //0x65
  {mov_h_m   , "mov"   , "h"  , "m"  , 0x00}, //0x66
  {mov_h_a   , "mov"   , "h"  , "a"  , 0x00}, //0x67
  {mov_l_b   , "mov"   , "l"  , "b"  , 0x00}, //0x68
  {mov_l_c   , "mov"   , "l"  , "c"  , 0x00}, //0x69
  {mov_l_d   , "mov"   , "l"  , "d"  , 0x00}, //0x6a
  {mov_l_e   , "mov"   , "l"  , "e"  , 0x00}, //0x6b
  {mov_l_h   , "mov"   , "l"  , "h"  , 0x00}, //0x6c
  {mov_l_l   , "mov"   , "l"  , "l"  , 0x00}, //0x6d
  {mov_l_m   , "mov"   , "l"  , "m"  , 0x00}, //0x6e
  {mov_l_a   , "mov"   , "l"  , "a"  , 0x00}, //0x6f
  {mov_m_b   , "mov"   , "m"  , "b"  , 0x00}, //0x70
  {mov_m_c   , "mov"   , "m"  , "c"  , 0x00}, //0x71
  {mov_m_d   , "mov"   , "m"  , "d"  , 0x00}, //0x72
  {mov_m_e   , "mov"   , "m"  , "e"  , 0x00}, //0x73
  {mov_m_h   , "mov"   , "m"  , "h"  , 0x00}, //0x74
  {mov_m_l   , "mov"   , "m"  , "l"  , 0x00}, //0x75
  {hlt       , "hlt"   , ""   , ""   , 0x00}, //0x76
  {mov_m_a   , "mov"   , "m"  , "a"  , 0x00}, //0x77
  {mov_a_b   , "mov"   , "a"  , "b"  , 0x00}, //0x78
  {mov_a_c   , "mov"   , "a"  , "c"  , 0x00}, //0x79
  {mov_a_d   , "mov"   , "a"  , "d"  , 0x00}, //0x7a
  {mov_a_e   , "mov"   , "a"  , "e"  , 0x00}, //0x7b
  {mov_a_h   , "mov"   , "a"  , "h"  , 0x00}, //0x7c
  {mov_a_l   , "mov"   , "a"  , "l"  , 0x00}, //0x7d
  {mov_a_m   , "mov"   , "a"  , "m"  , 0x00}, //0x7e
  {mov_a_a   , "mov"   , "a"  , "a"  , 0x00}, //0x7f
  {add_b     , "add"   , "b"  , ""   , 0x00}, //0x80
  {add_c     , "add"   , "c"  , ""   , 0x00}, //0x81
  {add_d     , "add"   , "d"  , ""   , 0x00}, //0x82
  {add_e     , "add"   , "e"  , ""   , 0x00}, //0x83
  {add_h     , "add"   , "h"  , ""   , 0x00}, //0x84
  {add_l     , "add"   , "l"  , ""   , 0x00}, //0x85
  {add_m     , "add"   , "m"  , ""   , 0x00}, //0x86
  {add_a     , "add"   , "a"  , ""   , 0x00}, //0x87
  {adc_b     , "adc"   , "b"  , ""   , 0x00}, //0x88
  {adc_c     , "adc"   , "c"  , ""   , 0x00}, //0x89
  {adc_d     , "adc"   , "d"  , ""   , 0x00}, //0x8a
  {adc_e     , "adc"   , "e"  , ""   , 0x00}, //0x8b
  {adc_h     , "adc"   , "h"  , ""   , 0x00}, //0x8c
  {adc_l     , "adc"   , "l"  , ""   , 0x00}, //0x8d
  {adc_m     , "adc"   , "m"  , ""   , 0x00}, //0x8e
  {adc_m     , "adc"   , "a"  , ""   , 0x00}, //0x8f
  {sub_b     , "sub"   , "b"  , ""   , 0x00}, //0x90
  {sub_c     , "sub"   , "c"  , ""   , 0x00}, //0x91
  {sub_d     , "sub"   , "d"  , ""   , 0x00}, //0x92
  {sub_e     , "sub"   , "e"  , ""   , 0x00}, //0x93
  {sub_h     , "sub"   , "h"  , ""   , 0x00}, //0x94
  {sub_l     , "sub"   , "l"  , ""   , 0x00}, //0x95
  {sub_m     , "sub"   , "m"  , ""   , 0x00}, //0x96
  {sub_a     , "sub"   , "a"  , ""   , 0x00}, //0x97
  {sbb_b     , "sbb"   , "b"  , ""   , 0x00}, //0x98
  {sbb_c     , "sbb"   , "c"  , ""   , 0x00}, //0x99
  {sbb_d     , "sbb"   , "d"  , ""   , 0x00}, //0x9a
  {sbb_e     , "sbb"   , "e"  , ""   , 0x00}, //0x9b
  {sbb_h     , "sbb"   , "h"  , ""   , 0x00}, //0x9c
  {sbb_l     , "sbb"   , "l"  , ""   , 0x00}, //0x9d
  {sbb_m     , "sbb"   , "m"  , ""   , 0x00}, //0x9e
  {sbb_a     , "sbb"   , "a"  , ""   , 0x00}, //0x9f
  {ana_b     , "ana"   , "b"  , ""   , 0x00}, //0xa0
  {ana_c     , "ana"   , "c"  , ""   , 0x00}, //0xa1
  {ana_d     , "ana"   , "d"  , ""   , 0x00}, //0xa2
  {ana_e     , "ana"   , "e"  , ""   , 0x00}, //0xa3
  {ana_h     , "ana"   , "h"  , ""   , 0x00}, //0xa4
  {ana_l     , "ana"   , "l"  , ""   , 0x00}, //0xa5
  {ana_m     , "ana"   , "m"  , ""   , 0x00}, //0xa6
  {ana_a     , "ana"   , "a"  , ""   , 0x00}, //0xa7
  {xra_b     , "xra"   , "b"  , ""   , 0x00}, //0xa8
  {xra_c     , "xra"   , "c"  , ""   , 0x00}, //0xa9
  {xra_d     , "xra"   , "d"  , ""   , 0x00}, //0xaa
  {xra_e     , "xra"   , "e"  , ""   , 0x00}, //0xab
  {xra_h     , "xra"   , "h"  , ""   , 0x00}, //0xac
  {xra_l     , "xra"   , "l"  , ""   , 0x00}, //0xad
  {xra_m     , "xra"   , "m"  , ""   , 0x00}, //0xae
  {xra_a     , "xra"   , "a"  , ""   , 0x00}, //0xaf
  {ora_b     , "ora"   , "b"  , ""   , 0x00}, //0xb0
  {ora_c     , "ora"   , "c"  , ""   , 0x00}, //0xb1
  {ora_d     , "ora"   , "d"  , ""   , 0x00}, //0xb2
  {ora_e     , "ora"   , "e"  , ""   , 0x00}, //0xb3
  {ora_h     , "ora"   , "h"  , ""   , 0x00}, //0xb4
  {ora_l     , "ora"   , "l"  , ""   , 0x00}, //0xb5
  {ora_m     , "ora"   , "m"  , ""   , 0x00}, //0xb6
  {ora_a     , "ora"   , "a"  , ""   , 0x00}, //0xb7
  {cmp_b     , "cmp"   , "b"  , ""   , 0x00}, //0xb8
  {cmp_c     , "cmp"   , "c"  , ""   , 0x00}, //0xb9
  {cmp_d     , "cmp"   , "d"  , ""   , 0x00}, //0xba
  {cmp_e     , "cmp"   , "e"  , ""   , 0x00}, //0xbb
  {cmp_h     , "cmp"   , "h"  , ""   , 0x00}, //0xbc
  {cmp_l     , "cmp"   , "l"  , ""   , 0x00}, //0xbd
  {cmp_m     , "cmp"   , "m"  , ""   , 0x00}, //0xbe
  {cmp_a     , "cmp"   , "a"  , ""   , 0x00}, //0xbf
  {rnz       , "rnz"   , ""   , ""   , 0x00}, //0xc0
  {pop_b     , "pop"   , "b"  , ""   , 0x00}, //0xc1
  {jnz       , "jnz"   , " "  , ""   , 0x20}, //0xc2
  {jmp       , "jmp"   , ""   , ""   , 0x20}, //0xc3
  {cnz       , "cnz"   , ""   , ""   , 0x20}, //0xc4
  {push_b    , "push"  , "b"  , ""   , 0x00}, //0xc5
  {_adi      , "adi"   , ""   , " "  , 0x10}, //0xc6
  {rst_0     , "rst"   , "0"  , ""   , 0x00}, //0xc7
  {rz        , "rz"    , " "  , ""   , 0x00}, //0xc8
  {ret       , "ret"   , ""   , ""   , 0x00}, //0xc9
  {jz        , "jz"    , ""   , ""   , 0x20}, //0xca
  {_invalid  , ""      , "x"  , "x"  , 0xff}, //0xcb
  {cz        , "cz"    , ""   , ""   , 0x20}, //0xcc
  {call      , "call"  , ""   , ""   , 0x20}, //0xcd
  {_aci      , "aci"   , ""   , " "  , 0x10}, //0xce
  {rst_1     , "rst"   , "1"  , ""   , 0x00}, //0xcf
  {rnc       , "rnc"   , ""   , ""   , 0x00}, //0xd0
  {pop_d     , "pop"   , "d"  , ""   , 0x00}, //0xd1
  {jnc       , "jnc"   , ""   , ""   , 0x20}, //0xd2
  {out       , "out"   , ""   , ""   , 0x10}, //0xd3
  {cnc       , "cnc"   , ""   , ""   , 0x20}, //0xd4
  {push_d    , "push"  , "d"  , ""   , 0x00}, //0xd5
  {_sui      , "sui"   , ""   , " "  , 0x20}, //0xd6
  {rst_2     , "rst"   , "2"  , ""   , 0x00}, //0xd7
  {rc        , "rc"    , ""   , ""   , 0x00}, //0xd8
  {_invalid  , ""      , "x"  , "x"  , 0xff}, //0xd9
  {jc        , "jc"    , " "  , ""   , 0x20}, //0xda
  {in        , "in"    , ""   , ""   , 0x10}, //0xdb
  {cc        , "cc"    , " "  , ""   , 0x20}, //0xdc
  {_invalid  , ""      , "x"  , "x"  , 0xff}, //0xdd
  {_sbi      , "sbi"   , ""   , " "  , 0x10}, //0xde
  {rst_3     , "rst"   , "3"  , ""   , 0x00}, //0xdf
  {rpo       , "rpo"   , ""   , ""   , 0x00}, //0xe0
  {pop_h     , "pop"   , "h"  , ""   , 0x00}, //0xe1
  {jpo       , "jpo"   , ""   , ""   , 0x20}, //0xe2
  {xthl      , "xthl"  , ""   , ""   , 0x00}, //0xe3
  {cpo       , "cpo"   , ""   , ""   , 0x20}, //0xe4
  {push_h    , "push"  , "h"  , ""   , 0x00}, //0xe5
  {_ani      , "ani"   , " "  , ""   , 0x10}, //0xe6
  {rst_4     , "rst"   , "4"  , ""   , 0x00}, //0xe7
  {rpe       , "rpe"   , ""   , ""   , 0x00}, //0xe8
  {pchl      , "pchl"  , ""   , ""   , 0x00}, //0xe9
  {jpe       , "jpe"   , ""   , ""   , 0x20}, //0xea
  {xchg      , "xchg"  , ""   , ""   , 0x00}, //0xeb
  {cpe       , "cpe"   , ""   , ""   , 0x20}, //0xec
  {_invalid  , ""      , "x"  , "x"  , 0xff}, //0xed
  {_xri      , "xri"   , ""   , " "  , 0x10}, //0xee
  {rst_5     , "rst"   , "5"  , ""   , 0x00}, //0xef
  {rp        , "rp"    , ""   , ""   , 0x00}, //0xf0
  {pop_psw   , "pop"   , "psw", ""   , 0x00}, //0xf1
  {jp        , "jp"    , ""   , ""   , 0x20}, //0xf2
  {di        , "di"    , ""   , ""   , 0x00}, //0xf3
  {cp        , "cp"    , ""   , ""   , 0x20}, //0xf4
  {push_psw  , "push"  , "psw", ""   , 0x00}, //0xf5
  {_ori      , "ori"   , ""   , " "  , 0x10}, //0xf6
  {rst_6     , "rst"   , "6"  , ""   , 0x00}, //0xf7
  {rm        , "rm"    , ""   , ""   , 0x00}, //0xf8
  {sphl      , "sphl"  , ""   , ""   , 0x00}, //0xf9
  {jm        , "jm"    , " "  , ""   , 0x20}, //0xfa
  {ei        , "ei"    , ""   , ""   , 0x00}, //0xfb
  {cm        , "cm"    , ""   , ""   , 0x20}, //0xfc
  {_invalid  , ""      , "x"  , "x"  , 0xff}, //0xfd
  {_cpi      , "cpi"   , ""   , " "  , 0x10}, //0xfe
  {rst_7     , "rst"   , "7"  , ""   , 0x00}, //0xff
}; 
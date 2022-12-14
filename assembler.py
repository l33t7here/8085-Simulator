# Author 
# https://github.com/ept221/8085-Assembler
# Notes:
# -> Add decimal and binary base functionality
##############################################################################################################
import re
import sys
import argparse
instructions = {
    'NOP':      0x00,
    'LXI B':    0x01,
    'STAX B':   0x02,
    'INX B':    0x03,
    'INR B':    0x04,
    'DCR B':    0x05,
    'MVI B':    0x06,
    'RLC':      0x07,
    'DAD B':    0x09,
    'LDAX B':   0x0A,
    'DCX B':    0x0B,
    'INR C':    0x0C,
    'DCR C':    0x0D,
    'MVI C':    0x0E,
    'RRC':      0x0F,
    'LXI D':    0x11,
    'STAX D':   0x12,
    'INX D':    0x13,
    'INR D':    0x14,
    'DCR D':    0x15,
    'MVI D':    0x16,
    'RAL':      0x17,
    'DAD D':    0x19,
    'LDAX D':   0x1A,
    'DCX D':    0x1B,
    'INR E':    0x1C,
    'DCR E':    0x1D,
    'MVI E':    0x1E,
    'RAR':      0x1F,
    'RIM':      0x20,
    'LXI H':    0x21,
    'SHLD':     0x22,
    'INX H':    0x23,
    'INR H':    0x24,
    'DCR H':    0x25,
    'MVI H':    0x26,
    'DAA':      0x27,
    'DAD H':    0x29,
    'LHLD':     0x2A,
    'DCX H':    0x2B,
    'INR L':    0x2C,
    'DCR L':    0x2D,
    'MVI L':    0x2E,
    'CMA':      0x2F,
    'SIM':      0x30,
    'LXI SP':   0x31,
    'STA':      0x32,
    'INX SP':   0x33,
    'INR M':    0x34,
    'DCR M':    0x35,
    'MVI M':    0x36,
    'STC':      0x37,
    'DAD SP':   0x39,
    'LDA':      0x3A,
    'DCX SP':   0x3B,
    'INR A':    0x3C,
    'DCR A':    0x3D,
    'MVI A':    0x3E,
    'CMC':      0x3F,
    'MOV B,B':  0x40,
    'MOV B,C':  0x41,
    'MOV B,D':  0x42,
    'MOV B,E':  0x43,
    'MOV B,H':  0x44,
    'MOV B,L':  0x45,
    'MOV B,M':  0x46,
    'MOV B,A':  0x47,
    'MOV C,B':  0x48,
    'MOV C,C':  0x49,
    'MOV C,D':  0x4A,
    'MOV C,E':  0x4B,
    'MOV C,H':  0x4C,
    'MOV C,L':  0x4D,
    'MOV C,M':  0x4E,
    'MOV C,A':  0x4F,
    'MOV D,B':  0x50,
    'MOV D,C':  0x51,
    'MOV D,D':  0x52,
    'MOV D,E':  0x53,
    'MOV D,H':  0x54,
    'MOV D,L':  0x55,
    'MOV D,M':  0x56,
    'MOV D,A':  0x57,
    'MOV E,B':  0x58,
    'MOV E,C':  0x59,
    'MOV E,D':  0x5A,
    'MOV E,E':  0x5B,
    'MOV E,H':  0x5C,
    'MOV E,L':  0x5D,
    'MOV E,M':  0x5E,
    'MOV E,A':  0x5F,
    'MOV H,B':  0x60,
    'MOV H,C':  0x61,
    'MOV H,D':  0x62,
    'MOV H,E':  0x63,
    'MOV H,H':  0x64,
    'MOV H,L':  0x65,
    'MOV H,M':  0x66,
    'MOV H,A':  0x67,
    'MOV L,B':  0x68,
    'MOV L,C':  0x69,
    'MOV L,D':  0x6A,
    'MOV L,E':  0x6B,
    'MOV L,H':  0x6C,
    'MOV L,L':  0x6D,
    'MOV L,M':  0x6E,
    'MOV L,A':  0x6F,
    'MOV M,B':  0x70,
    'MOV M,C':  0x71,
    'MOV M,D':  0x72,
    'MOV M,E':  0x73,
    'MOV M,H':  0x74,
    'MOV M,L':  0x75,
    'HLT':      0x76,
    'MOV M,A':  0x77,
    'MOV A,B':  0x78,
    'MOV A,C':  0x79,
    'MOV A,D':  0x7A,
    'MOV A,E':  0x7B,
    'MOV A,H':  0x7C,
    'MOV A,L':  0x7D,
    'MOV A,M':  0x7E,
    'MOV A,A':  0x7F,
    'ADD B':    0x80,
    'ADD C':    0x81,
    'ADD D':    0x82,
    'ADD E':    0x83,
    'ADD H':    0x84,
    'ADD L':    0x85,
    'ADD M':    0x86,
    'ADD A':    0x87,
    'ADC B':    0x88,
    'ADC C':    0x89,
    'ADC D':    0x8A,
    'ADC E':    0x8B,
    'ADC H':    0x8C,
    'ADC L':    0x8D,
    'ADC M':    0x8E,
    'ADC A':    0x8F,
    'SUB B':    0x90,
    'SUB C':    0x91,
    'SUB D':    0x92,
    'SUB E':    0x93,
    'SUB H':    0x94,
    'SUB L':    0x95,
    'SUB M':    0x96,
    'SUB A':    0x97,
    'SBB B':    0x98,
    'SBB C':    0x99,
    'SBB D':    0x9A,
    'SBB E':    0x9B,
    'SBB H':    0x9C,
    'SBB L':    0x9D,
    'SBB M':    0x9E,
    'SBB A':    0x9F,
    'ANA B':    0xA0,
    'ANA C':    0xA1,
    'ANA D':    0xA2,
    'ANA E':    0xA3,
    'ANA H':    0xA4,
    'ANA L':    0xA5,
    'ANA M':    0xA6,
    'ANA A':    0xA7,
    'XRA B':    0xA8,
    'XRA C':    0xA9,
    'XRA D':    0xAA,
    'XRA E':    0xAB,
    'XRA H':    0xAC,
    'XRA L':    0xAD,
    'XRA M':    0xAE,
    'XRA A':    0xAF,
    'ORA B':    0xB0,
    'ORA C':    0xB1,
    'ORA D':    0xB2,
    'ORA E':    0xB3,
    'ORA H':    0xB4,
    'ORA L':    0xB5,
    'ORA M':    0xB6,
    'ORA A':    0xB7,
    'CMP B':    0xB8,
    'CMP C':    0xB9,
    'CMP D':    0xBA,
    'CMP E':    0xBB,
    'CMP H':    0xBC,
    'CMP L':    0xBD,
    'CMP M':    0xBE,
    'CMP A':    0xBF,
    'RNZ':      0xC0,
    'POP B':    0xC1,
    'JNZ':      0xC2,
    'JMP':      0xC3,
    'CNZ':      0xC4,
    'PUSH B':   0xC5,
    'ADI':      0xC6,
    'RST 0':    0xC7,
    'RZ':       0xC8,
    'RET':      0xC9,
    'JZ':       0xCA,
    'CZ':       0xCC,
    'CALL':     0xCD,
    'ACI':      0xCE,
    'RST 1':    0xCF,
    'RNC':      0xD0,
    'POP D':    0xD1,
    'JNC':      0xD2,
    'OUT':      0xD3,
    'CNC':      0xD4,
    'PUSH D':   0xD5,
    'SUI':      0xD6,
    'RST 2':    0xD7,
    'RC':       0xD8,
    'JC':       0xDA,
    'IN':       0xDB,
    'CC':       0xDC,
    'SBI':      0xDE,
    'RST 3':    0xDF,
    'RPO':      0xE0,
    'POP H':    0xE1,
    'JPO':      0xE2,
    'XTHL':     0xE3,
    'CPO':      0xE4,
    'PUSH H':   0xE5,
    'ANI':      0xE6,
    'RST 4':    0xE7,
    'RPE':      0xE8,
    'PCHL':     0xE9,
    'JPE':      0xEA,
    'XCHG':     0xEB,
    'CPE':      0xEC,
    'XRI':      0xEE,
    'RST 5':    0xEF,
    'RP':       0xF0,
    'POP PSW':  0xF1,
    'JP':       0xF2,
    'DI':       0xF3,
    'CP':       0xF4,
    'PUSH PSW': 0xF5,
    'ORI':      0xF6,
    'RST 6':    0xF7,
    'RM':       0xF8,
    'SPHL':     0xF9,
    'JM':       0xFA,
    'EI':       0xFB,
    'CM':       0xFC,
    'CPI':      0xFE,
    'RST 7':    0xFF
    }
bin_op = {
    '+',
    '-',
}

uni_op = {
    '+',
    '-'
}

mnm_0 = {
	'XCHG',
	'XTHL',
	'SPHL',
	'PCHL',
	'RET',
	'RC',
	'RNC',
	'RZ',
	'RNZ',
	'RP',
	'RM',
	'RPE',
	'RPO',
	'RLC',
	'RRC',
	'RAL',
	'RAR',
	'CMA',
	'STC',
	'CMC',
	'DAA',
	'EI',
	'DI',
	'NOP',
	'HLT',
	'RIM',
	'SIM',
}

mnm_0_e = {
    'ADI': "data",
    'ACI': "data",
    'SUI': "data",
    'SBI': "data",
    'STA': "address",
    'LDA': "address",
    'SHLD': "address",
    'LHLD': "address",
    'JMP': "address",
    'JC': "address",
    'JNC': "address",
    'JZ': "address",
    'JNZ': "address",
    'JP': "address",
    'JM': "address",
    'JPE': "address",
    'JPO': "address",
    'CALL': "address",
    'CC': "address",
    'CNC': "address",
    'CZ': "address",
    'CNZ': "address",
    'CP': "address",
    'CM': "address",
    'CPE': "address",
    'CPO': "address",
    'IN': "data",
    'OUT': "data",
    'ANI': "data",
    'XRI': "data", 
    'ORI': "data",
    'CPI': "data",
}

mnm_1 = {
    'STAX',
    'LDAX',
    'PUSH',
    'POP',
    'RST',
    'INR',
    'DCR',
    'INX',
    'DCX',
    'ADD',
    'ADC',
    'DAD', 
    'SUB',
    'SBB',
    'ANA',
    'XRA',
    'ORA',
    'CMP',
}

mnm_1_e = {
	'MVI': "data",
    'LXI': "address",
}

mnm_2 = {
	'MOV',
}

drct_1 = {
	'ORG',
	'DS'
}

drct_p = {
	'DB',
}

drct_w = {
	'EQU'
}

reg = {
    'A',
    'B',
    'C',
    'D',
    'E',
    'H',
    'L',
    'SP',
    'PSW',
    'M',
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7'
}

reserved_mnm_0_e = {key for key in mnm_0_e}
reserved_mnm_1_e = {key for key in mnm_1_e}
reserved =  bin_op | uni_op | mnm_0 | reserved_mnm_0_e | mnm_1 | reserved_mnm_1_e | mnm_2 | drct_1 | drct_p | drct_w | reg 

##############################################################################################################
# Support Classes

class Symbol:

    def __init__(self):
        self.labelDefs = {}
        self.eightBitDefs = {}
        self.sixteenBitDefs = {}
        self.expr = []

class Code:

    def __init__(self):
        self.data = []
        self.address = 0
        self.label = ""

    def write(self, data, line, instrct = ""):
        # Format: [line] [lineNumStr] [address] [label] [instruction + argument] [hex code] [comment]

        if(self.address > 65535):
            error("Cannot write past 0xFFFF. Out of memory!",line)
            sys.exit(2)

        addressStr = '0x{0:0{1}X}'.format(self.address,4)

        if(data != "expr"):
            data = '0x{0:0{1}X}'.format(data,2)

        comment = ''
        lineNumStr = ''
        pc = line[0][1]
        if(len(self.data) == 0 or pc != self.data[-1][0][0][1]):
            comment = line[2]
            lineNumStr = str(line[0][0])

        self.data.append([line, lineNumStr, addressStr, self.label, instrct, data, comment])
        self.address += 1
        self.label = ""

    def update(self, data, index):
        self.data[index][5] = '0x{0:0{1}X}'.format(data,2)

##############################################################################################################
# File reading functions

def read(name):
    # This function reads in lines from the asm file
    # It processes them and puts them into the form:
    # [[Line_number, Program_Counter] [body] [comment]]
    # Line_number corrisponds to the line on the 
    # source code. the Program_Counter is incremented
    # every time there is a non-empty line. Note that
    # two consecutive PC locations do NOT nessisarily
    # corrispond to two consecutive address locations

    # [[Line_number, Program_Counter] [body] 'comment']
    
    file = open(name, 'r')
    lines = []
    lineNumber = 0
    pc = 0
    
    for lineNumber, line in enumerate(file, start = 1):
        line = line.strip()
        line = line.upper()
        if(line):
            block = []
            rest = []
            comment = ''
            commentIndex = line.find(";")
            if(commentIndex != -1):
                comment = line[commentIndex:]
                rest = line[:commentIndex].strip()
            else:
                rest = line

            block.append([lineNumber, pc])
            if(rest):
                split_rest = re.split(r'([-+,\s]\s*)', rest)
                split_rest = [word for word in split_rest if not re.match(r'^\s*$',word)]
                split_rest = list(filter(None, split_rest))
                block.append(split_rest)
            else:
                block.append([])
            block.append(comment)
            lines.append(block)
            pc += 1
            
    file.close()
    return lines

##############################################################################################################
# Utility functions

def error(message, line):
    print("Error at line " + str(line[0][0]) + ": " + message)

def output(code, name):
    # Format: [line] [lineNumStr] [address] [label] [instruction + argument] [hex code] [comment]
    f = open(name,'w') if name else sys.stdout
    for eachCode in code.data:
        f.write(eachCode[5]+"\n")
    if f is not sys.stdout:
        f.close()

##############################################################################################################
# Directive functions
def org(arg, symbols, code, line):
    val = evaluate(arg, symbols, code.address)
    if(len(val) == 1):
        num = val[0]
        if(num < 0):
            error("Expression must be positive!",line)
            return 0
        elif(num < code.address):
            error("Cannot move origin backwards!",line)
            return 0
        elif(num > 65535):
            error("Cannot set origin past 0xFFFF!",line)
            return 0
        else:
            code.address = num
            if(code.label):
                symbols.labelDefs[code.label[:-1]] = '{0:0{1}X}'.format(num,4)
            return 1
    else:
        error("Expression depends on unresolved symbol!",line)
        return 0

def db(args, symbols, code, line):
    for expr in args:
        val = evaluate(expr, symbols, code.address)
        if(len(val) == 1):
            num = val[0]
            if(num < 0):
                error("Expression must be positive!",line)
                return 0
            elif(num > 255):
                error("Expression too large! Must evaluate to an 8-bit number!", line)
                return 0
            else:
                code.write(num,line,instrct="DB")
        else:
            error("Expression depends on unresolved symbol!",line)
            return 0
    return 1

def equ(args, symbols, code, line):
    name = args[0][1]
    if(name in reserved):
        error("Cannot use reserved keyword in equ directive!",line)
        return 0
    elif(name in (symbols.eightBitDefs, symbols.sixteenBitDefs)):
        error("Symbol already defined!",line)
        return 0
    elif(name in symbols.labelDefs):
        error("Symbol conflicts with previous label definition!",line)
        return 0

    val = evaluate(args[1], symbols, code.address)
    if(len(val) == 1):
        num = val[0]
        if num > 65535:
            error("Expression evaluates to value greater than 0xFFFF!",line)
            return 0
        elif num > 255:
            symbols.sixteenBitDefs[name] = '{0:0{1}X}'.format(num,4)
            return 1
        elif num >= 0:
            symbols.eightBitDefs[name] = '{0:0{1}X}'.format(num,2)
            return 1
        else:
            error("Expression must be positive!",line)
            return 0
    else:
        error("Expression depends on unresolved symbol!",line)
        return 0

def ds(arg, symbols, code, line):
    val = evaluate(arg, symbols, code.address)
    if(len(val) == 1):
        num = val[0]
        if(num < 0):
            error("Expression must be positive!",line)
            return 0
        elif(num + code.address > 65536):
            error("Cannot define that much storage! Only " + str((65536 - code.address)) + 
                  " bytes left. Overflow by " + str(num + code.address - 65536) + ".",line)
            return 0
        else:
            code.address += num
            return 1
    else:
        error("Expression depends on unresolved symbol!",line)
        return 0

directives = {
    #Format:
    # [function, min_args, max_args, name]
    # -1 means no bound
    "ORG": [org, 1, 1, "ORG"],
    "DB":  [db, 1, -1, "DB"],
    "EQU": [equ, 2, 2, "EQU"],
    "DS":  [ds, 1, 1, "DS"],
}
     
def secondPass(symbols, code):
    # Format: [line] [lineNumStr] [address] [label] [instruction + argument] [hex code] [comment]
    i = 0
    address = 0
    while i < len(code.data):
        codeLine = code.data[i]
        line = codeLine[0]
        data = codeLine[5]
        if(data == "expr"):
            expr, kind  = symbols.expr.pop(0)
            val = evaluate(expr, symbols, address)
            if(len(val) == 1):
                numb = val[0]
                if(numb < 0):
                    error("Expression must be positive!",line)
                    return 0
                elif(kind == "data"):
                    if(numb > 255):
                        error("Expression must evaluate to 8-bit number!",line)
                        return 0
                    else:
                        code.update(numb,i)
                elif(kind == "address"):
                    if(numb > 65535):
                        error("Expression must evaluate to 16-bit number!",line)
                        return 0
                    else:
                        code.update((numb & 0xff),i)
                        code.update((numb >> 8),i+1)
                        i += 1
            else:
                error("Expression relies on unresolved symbol!",line)
                return 0
        else:
            address = int(codeLine[2], base=16) 
        i += 1

def lexer(lines):
    tokens = []
    code_lines = [x for x in lines if len(x[1])]
    for line in code_lines:
        tl = []
        for word in line[1]:
            word = word.strip()
            if word in mnm_0:
                tl.append(["<mnm_0>", word])
            elif(re.match(r'^(0[Xx])?[0-9A-Fa-f]{2}$', word)):
                tl.append(["<08nm>", word])
            elif word in mnm_0_e:
                tl.append(["<mnm_0_e>", word])
            elif word in mnm_1:
                tl.append(["<mnm_1>", word])
            elif word in mnm_1_e:
                tl.append(["<mnm_1_e>", word])
            elif word in mnm_2:
                tl.append(["<mnm_2>", word])
            elif word in reg:
                tl.append(["<reg>", word])
            elif word == ",":
                tl.append(["<comma>", word])
            elif word == "+":
                tl.append(["<plus>", word])
            elif word == "-":
                tl.append(["<minus>", word])
            elif word in drct_1:
                tl.append(["<drct_1>", word])
            elif word in drct_p:
                tl.append(["<drct_p>", word])
            elif word in drct_w:
                tl.append(["<drct_w>", word])
            elif re.match(r'^.+:$',word):
                tl.append(["<lbl_def>", word])
            elif(re.match(r'^(0[Xx])?[0-9A-Fa-f]{4}$', word)):
                tl.append(["<16nm>", word])
            elif(re.match(r'^[A-Za-z_]+[A-Za-z0-9_]*$', word)):
                tl.append(["<symbol>", word])
            elif word == "$":
                tl.append(["<lc>", word])
            else:
                tl.append(["<idk_man>", word])
                error("Unknown token: " + word, line)
                return [0 , 0]

        tokens.append(tl)

    return [code_lines, tokens]
######################################################################################
def evaluate(expr, symbols, address):
    sign, pop, result = 1, 2, 0
    while(expr):
        ###################################
        if(len(expr) >= 2):
            pop = 2
            if(expr[-2][0] == "<plus>"):
                sign = 1
            else:
                sign = -1
        else:
            pop = 1
            sign = 1
        ###################################
        if(expr[-1][0] in {"<08nm>", "<16nm>", "<numb>"}):
            result += sign*int(expr[-1][1], base=16)
            expr = expr[:-pop]
        elif(expr[-1][0] == "<lc>"):
            result += sign*(address)
            expr = expr[:-pop] 
        else:
            if(expr[-1][1] in symbols.eightBitDefs):
                result += sign*int(symbols.eightBitDefs[expr[-1][1]], base=16)
                expr = expr[:-pop]
            elif(expr[-1][1] in symbols.sixteenBitDefs):
                result += sign*int(symbols.sixteenBitDefs[expr[-1][1]], base=16)
                expr = expr[:-pop]
            elif(expr[-1][1] in symbols.labelDefs):
                result += sign*int(symbols.labelDefs[expr[-1][1]], base=16)
                expr = expr[:-pop]
            else:
                expr += [["<plus>", "+"],["<numb>", hex(result)]]
                return expr
        ###################################
    return [result]

######################################################################################
# Grammar:
#
# <line> ::= <lbl_def> [<drct>] [<code>]
#          | <drct> [<code>]
#          | <code>
#
# <code> ::= <mnm_0>
#          | <mnm_0_e> <expr>
#          | <mnm_1> <reg>
#          | <mnm_1_e> <reg> "," <expr>
#          | <mnm_2> <reg> "," <reg>
#
# <expr> ::= [ (<plus> | <minus>) ] <numb> { (<plus> | <minus>) <numb> }
#
# <drct> ::= <drct_1> <expr>
#          | <drct_p> <expr> { ","  <expr> }
#          | <symbol> <drct_w> <expr>
#
# <numb> ::= <08nm> | <16nm> | <symbol> | <lc>
######################################################################################
def parse(lines, symbols, code):

    code_lines, tokenLines = lexer(lines)
    if(code_lines == 0):
        sys.exit(1)

    tree = []

    for tokens, line in zip(tokenLines, code_lines):
        parsed_line = parse_line(tokens, symbols, code, line)
        if(parsed_line[0] == "<error>"):
            sys.exit(1)
        tree.append(parsed_line)

    status = secondPass(symbols, code)
    if(status == 0):
        sys.exit(1)
######################################################################################
def parse_expr(tokens, symbols, code, line):
    data = ["<expr>"]
    er = ["<error>"]
    if not tokens:
        return 0
    ##################################################
    while(tokens):
        if(tokens[0][0] in {"<plus>", "<minus>"}):
            data.append(tokens.pop(0))
        elif(len(data) > 1):
            return data
        if(len(data) > 1 and (not tokens)):
            error("Expression missing number/symbol!",line)
            return er
        if(tokens[0][0] not in {"<08nm>", "<16nm>", "<symbol>", "<lc>"}):
            if(tokens[0][0] not in {"<plus>", "<minus>"}):
                if(len(data) > 1):
                    error("Expression has bad identifier!",line)
                    return er
                else:
                    return 0
            else:
                error("Expression has extra operator!",line)
                return er
        data.append(tokens.pop(0))
    return data
######################################################################################
def parse_lbl_def(tokens, symbols, code, line):
    er = ["<error>"]
    if not tokens:
        return 0
    if(tokens[0][0] == "<lbl_def>"):
        lbl = tokens[0][1]
        if lbl[:-1] in symbols.labelDefs:
            error("Label already in use!",line)
            return er
        elif lbl[:-1] in reserved:
            error("Label cannot be keyword!",line)
            return er
        elif(re.match(r'^(0[Xx])?[0-9A-Fa-f]{2}$', lbl[:-1]) or
             re.match(r'^(0[Xx])?[0-9A-Fa-f]{4}$', lbl[:-1])):
            error("Label cannot be hex number!",line)
            return er
        elif lbl[:-1] in (symbols.eightBitDefs, symbols.sixteenBitDefs):
            error("Label conflicts with previous symbol definition",line)
            return er
        else:
            symbols.labelDefs[lbl[:-1]] = '{0:0{1}X}'.format(code.address,4)
            code.label = lbl
        return tokens.pop(0)
    else:
        return 0

######################################################################################
def parse_drct(tokens, symbols, code, line):
    args = [tokens, symbols, code, line]
    data = ["<drct>"]
    er = ["<error>"]
    if not tokens:
        return 0
    ##################################################
    # [drct_1]
    if(tokens[0][0] == "<drct_1>"):
        data.append(tokens.pop(0))
        if(not tokens):
            error("Directive missing argument!",line)
            return er
        expr = parse_expr(*args)
        if(not expr):
            error("Directive has bad argument!", line)
            return er
        if(expr == er):
            return er
        data.append(expr)
        arg = data[2][1:]
        status = directives[data[1][1]][0](arg,symbols,code,line)
        if not status:
            return er
        return data
    ##################################################
    # [drct_p]
    elif(tokens[0][0] in {"<drct_p>", "<08nm>"}):
        drct_p = tokens[0][1]
        if(tokens[0][0] == "<08nm>"):
            if(tokens[0][1] != "DB"):
                return 0
            tokens[0][0] = "<drct_p>"
        data.append(tokens.pop(0))

        if(not tokens):
            error("Directive missing argument!",line)
            return er
        expr = parse_expr(*args)
        if(not expr):
            error("Directive has bad argument!",line)
            return er
        elif(expr == er):
            return er
        data.append(expr)

        while(tokens):
            if(tokens[0][0] != "<comma>"):
                error("Missing comma!",line)
                return er
            data.append(tokens.pop(0))
            if(not tokens):
                error("Directive missing last argument or has extra comma!",line)
                return er
            expr = parse_expr(*args)
            if(not expr):
                error("Directive has bad argument!",line)
                return er
            elif(expr == error):
                return er
            data.append(expr)

        d_args = [x[1:] for x in data[2:] if x[0] != "<comma>"]
        status = directives[drct_p][0](d_args,symbols,code,line)
        if not status:
            return er
        return data
    ##################################################
    # [drct_w]
    elif(tokens[0][0] == "<symbol>"):
        data.append(tokens.pop(0))
        if(not tokens or tokens[0][0] != "<drct_w>"):
            error("Bad Identifier!",line)
            return er
        data.append(tokens.pop(0))
        if(not tokens):
            error("Directive missing argument!",line)
            return er
        expr = parse_expr(*args)
        if(not expr):
            error("Directive has bad argument!",line)
            return er
        elif(expr == er):
            return er
        data.append(expr)
        ##############################################
        arg1 = data[1]
        arg2 = data[3][1:]
        status = directives[data[2][1]][0]([arg1,arg2],symbols,code,line)
        if not status:
            return er
        return data
    elif(tokens[0][0] == "<drct_w>"):
        error("Directive missing initial argument!",line)
        return er

    return 0

######################################################
def parse_code(tokens, symbols, code, line):
    args = [tokens, symbols, code, line]
    data = ["<code>"]
    er = ["<error>"]
    if not tokens:
        return 0
    ##################################################
    # [mnm_0]
    if(tokens[0][0] == "<mnm_0>"):
        inst = tokens[0][1]
        data.append(tokens.pop(0))
        code.write(instructions[inst],line,instrct=inst)
        return data
    ##################################################
    # [mnm_0_e]
    elif(tokens[0][0] in {"<mnm_0_e>", "<08nm>"}):
        if(tokens[0][0] == "<08nm>"):
            if(tokens[0][1] != "CC"):
                return 0
            tokens[0][0] = "<mnm_0_e>"
        inst = tokens[0][1]
        data.append(tokens.pop(0))

        if(not tokens):
            error("Instruction missing argument!",line)
            return er

        expr = parse_expr(*args)
        if(not expr):
            error("Instruction has bad argument!",line)
            return er
        if(expr == er):
            return er
        data.append(expr)

        expr_str = " ".join([x[1] for x in expr[1:]])
        if(inst in instructions):
            code.write(instructions[inst],line,instrct=inst+" "+expr_str)
        else:
            error("Bad instruction: "+inst,line)
            return er

        val = evaluate(expr[1:],symbols,code.address-1)
        if(len(val) == 1):
            numb = val[0]
            if(numb < 0):
                error("Expression must be positive!",line)
                return er
            elif(mnm_0_e[inst] == "data"):
                if(numb > 255):
                    error("Expression must evaluate to 8-bit number!",line)
                    return er
                code.write(numb,line)
            elif(mnm_0_e[inst] == "address"):
                if(numb > 65535):
                    error("Expression must evaluate to 16-bit number!",line)
                    return er
                else:
                    code.write((numb & 0xff),line)
                    code.write((numb >> 8),line)
        else:
            symbols.expr.append([val,mnm_0_e[inst]])
            code.write("expr",line)
            if(mnm_0_e[inst] == "address"):
                code.write("expr",line)
        return data

    ##################################################
    # [mnm_1]
    elif(tokens[0][0] == "<mnm_1>"):
        inst = tokens[0][1]
        data.append(tokens.pop(0))
        if(not tokens):
            error("Instruction missing register/register-pair",line)
            return er
        if(tokens[0][0] != "<reg>"):
            error("Instruction has bad register/register-pair",line)
            return er
        reg = tokens[0][1]
        data.append(tokens.pop(0))
        if(inst+" "+reg in instructions):
            code.write(instructions[inst+" "+reg],line,instrct=inst+" "+reg)
        else:
            error("Bad instruction: "+inst+" "+reg,line)
            return er
        return data
    ##################################################
    # [mnm_1_e]
    elif(tokens[0][0] == "<mnm_1_e>"):
        inst = tokens[0][1]
        data.append(tokens.pop(0))
        if(not tokens):
            error("Instruction missing register/register-pair!",line)
            return er
        if(tokens[0][0] != "<reg>"):
            error("Instruction has bad register/register-pair!",line)
            return er
        reg = tokens[0][1]
        data.append(tokens.pop(0))
        if(not tokens):
            error("Instruction missing comma and argument!",line)
            return er
        if(tokens[0][0] != "<comma>"):
            if(tokens[0][0] not in {"<08nm>", "<16nm>", "<symbol>"}):
                error("Instruction has bad argument!",line)
                return er
            error("Instruction missing comma!",line)
            return er
        data.append(tokens.pop(0))
        if(not tokens):
            error("Instruction missing argument!",line)
            return er
        expr = parse_expr(*args)
        if(not expr):
            error("Instruction has bad argument!",line)
            return er
        elif(expr == er):
            return er
        data.append(expr)
        instStr = inst+" "+reg

        expr_str = " ".join([x[1] for x in expr[1:]])
        if(instStr in instructions):
            code.write(instructions[instStr],line,instrct=instStr+", "+expr_str)
        else:
            error("Bad instruction: "+instStr,line)
            return er

        val = evaluate(expr[1:],symbols,code.address-1)
        if(len(val) == 1):
            numb = val[0]
            if(numb < 0):
                error("Expression must be positive!",line)
                return er
            elif(mnm_1_e[inst] == "data"):
                if(numb > 255):
                    error("Expression must evaluate to 8-bit number!",line)
                    return er
                code.write(numb,line)
            elif(mnm_1_e[inst] == "address"):
                if(numb > 65535):
                    error("Expression must evaluate to 16-bit number!",line)
                    return er
                else:
                    code.write((numb & 0xff),line)
                    code.write((numb >> 8),line)
        else:
            symbols.expr.append([val,mnm_1_e[inst]])
            code.write("expr",line)
            if(mnm_1_e[inst] == "address"):
                code.write("expr",line)

        return data

    ##################################################
    # [mnm_2]
    elif(tokens[0][0] == "<mnm_2>"):
        inst = tokens[0][1]
        data.append(tokens.pop(0))
        if(not tokens):
            error("Instruction missing register/register-pair!",line)
            return er
        if(tokens[0][0] != "<reg>"):
            error("Instruction has bad register/register-pair!",line)
            return er
        reg1 = tokens[0][1]
        data.append(tokens.pop(0))
        if(not tokens):
            error("Instruction missing comma and register/register-pair!",line)
            return er
        if(tokens[0][0] != "<comma>"):
            if(tokens[0][0] != "<reg>"):
                error("Instruction has bad register/register-pair!",line)
                return er
            error("Instruction missing comma!",line)
            return er
        data.append(tokens.pop(0))
        if(not tokens):
            error("Instruction missing register/register-pair!",line)
            return er
        if(tokens[0][0] != "<reg>"):
            error("Instruction has bad register/register-pair!",line)
            return er
        reg2 = tokens[0][1]
        data.append(tokens.pop(0))

        instStr = inst+" "+reg1+","+reg2
        if(instStr in instructions):
            code.write(instructions[instStr],line,instrct=instStr)
        else:
            error("Bad instruction: "+instStr,line)
            return er
        return data

    return 0
######################################################################################
def parse_line(tokens, symbols, code, line):
    data = ["<line>"]
    er = ["<error>"]
    if(len(tokens) == 0):
        return 0
    ################################
    # [lbl_def]
    lbl_def = parse_lbl_def(tokens, symbols, code, line)
    if(lbl_def):
        if(lbl_def == er):
            return er
        data.append(lbl_def)
    ################################
    # [drct]
    drct = parse_drct(tokens, symbols, code, line)
    if(drct):
        if(drct == er):
            return er
        data.append(drct)
    ################################
    # [code]
    code = parse_code(tokens, symbols, code, line)
    if(code):
        if(code == er):
            return er
        data.append(code)
    ###############################
    # check to see that we have at
    # least one of lbl_def, drct,
    # or code
    if(len(data) < 2):
        tokens.pop(0)
        error("Bad Initial Identifier!",line)
        return er
    ###############################
    # check to see if we have any
    # tokens left
    if(len(tokens)):   
        error("Bad Final Identifier!",line)
        return er
    ###############################
    # everything's good
    return data

######################################################################################
# Main program

code = Code()
symbols = Symbol()

outFile = ""
discription = 'A simple 8085 assembler.'

p = argparse.ArgumentParser(description = discription)
p.add_argument("source", help="source file")
args = p.parse_args()
if(args.source):
    outFile = args.source

args.address, args.label, args.instruction, args.hex, args.comment = False, False, False, True, False

parse(read(args.source),symbols,code)
output(code, (args.source.rsplit('.', maxsplit=1)[0]+".hex"))
print(args.source.rsplit('.', maxsplit=1)[0]+".hex " + "Created SuccesssFully")
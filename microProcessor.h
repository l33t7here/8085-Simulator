#include <stdbool.h>
typedef unsigned char data;
typedef unsigned short address;

#define INSTRUCTION_MEM_LIMIT 10000

typedef struct _8085MP{
  data a;
  data b;
  data c;
  data d;
  data e;
  data h;
  data l;
  data flag;
  address sp;
  address pc;
  data memory[0xffff];

  // Special Register
  address instruction_register;

}_8085MP;

// Because They Will Return Data Which is Of 16 Bit
// To Handle That We Have Used Address stuff
// Here Address Representing 16 Bit Data
_8085MP* createNewMachine();
data getCarry(_8085MP *Machine);
data getParity(_8085MP *Machine);
data getSign(_8085MP *Machine);
data getZero(_8085MP *Machine);
data getAC(_8085MP *Machine);
bool execute(_8085MP *machine, address start_address);
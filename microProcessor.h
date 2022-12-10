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
  data *memory;

  // Special Register
  address instruction_register;

}_8085MP;

// Because They Will Return Data Which is Of 16 Bit
// To Handle That We Have Used Address stuff
// Here Address Representing 16 Bit Data
_8085MP* createNewMachine();
bool execute(_8085MP *machine, address start_address);
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "microProcessor.h"
#include <signal.h>
#include <string.h>
bool loadMachine(_8085MP *machine, char *fileName){
    FILE *AsmFile = fopen(fileName, "r");
    char c;
    int totalLines = 0;
    for (c = getc(AsmFile); c != EOF; c = getc(AsmFile))
        if (c == '\n')
            totalLines = totalLines + 1;
    if(totalLines > 0xffff){
        free(AsmFile);
        return false;
    }
    unsigned int eachLineValue;
    totalLines = 0;
    fseek(AsmFile, 0, SEEK_SET);
    while(fscanf(AsmFile, "%x", &eachLineValue) == 1){
        machine->memory[totalLines++] = (data )eachLineValue;
    }
    free(AsmFile);
    return true;
}
bool runProgram(WINDOW* flags, WINDOW * uPM, WINDOW *instre, char *fileName){
     _8085MP *newMachine = createNewMachine();
     if(!loadMachine(newMachine, fileName))
        return false;
     execute(newMachine, 0x0000);
     box(flags, 0,0);
     mvwprintw(flags ,1,1, " ---Registers--- ");
     mvwprintw(flags ,3,1, " Accumlator: 0x%02x", newMachine->a);
     mvwprintw(flags ,5,1, " B: 0x%02x  C: 0x%02x", newMachine->b,newMachine->c);
     mvwprintw(flags ,6,1, " D: 0x%02x  E: 0x%02x", newMachine->d,newMachine->e);
     mvwprintw(flags ,7,1, " H: 0x%02x  L: 0x%02x", newMachine->h,newMachine->l);
     mvwprintw(flags ,10,1, "%s", " -----Flags----- ");
     mvwprintw(flags ,12,1,  " C.Value: 0x%02x ", newMachine->flag);
     mvwprintw(flags ,14,1,  " Sign   : %d", getSign(newMachine) != 0);
     mvwprintw(flags ,15,1,  " Zero   : %d", getZero(newMachine) != 0);
     mvwprintw(flags ,16,1,  " AC     : %d", getAC(newMachine) != 0);
     mvwprintw(flags ,17,1,  " Parity : %d", getParity(newMachine) != 0);
     mvwprintw(flags ,18,1,  " Carry  : %d", getCarry(newMachine) != 0);
     wrefresh(flags);
     mvwprintw(uPM ,26,3, " .__ .__..__ .__.. ");
     mvwprintw(uPM ,27,3, "[ __|  |[__)[__]|   ");
     mvwprintw(uPM ,28,3, "[_./|__||   |  ||___");
     wrefresh(uPM);
     mvwprintw(instre ,1,1, " --Opcode/Memory--");
     box(instre, 0,0);
     for(int i = 0; i < 17; i++){
        mvwprintw(instre ,4+i,1, "0x%02x 0x%02x 0x%02x 0x%02x ", newMachine->memory[i],newMachine->memory[i+1], newMachine->memory[i+2],newMachine->memory[i+3]);
     }
     wrefresh(instre);
     return true;
     
}
void clearFileName(WINDOW *uPM){
    mvwprintw(uPM, 27,3, "No File Found ! ");
    mvwprintw(uPM, 28,3, "Try Again !     ");
    wrefresh(uPM);
    getch();
    mvwprintw(uPM, 27,3, "                ");
    mvwprintw(uPM, 28,3, "                ");
}
char * takeFileName(WINDOW *uPM, char *fileName){
    int index = 0;
    int ch;
    wmove(uPM, 27,3);
    wrefresh(uPM);
    while((ch = getch()) != '\n' && index < 34){
        if(ch == 127){
            if(index > 0){
                index--;
                mvwprintw(uPM ,27+(index/18),(index%18)+3, " ");
            }
        }else{
            fileName[index++] = ch;
             mvwprintw(uPM ,27+(index/18),(index%18 + index/18)+2, "%c", ch);
        }
        wrefresh(uPM);
    }
    fileName[index] = '\0';
    FILE *a = fopen(fileName, "r");
    if(a == NULL){
        free(a);
        clearFileName(uPM);
        return takeFileName(uPM, fileName);
    }
    return fileName;
}

void handle_resize(){
   doupdate();
}
int main(int argc, char * argv[]) {
    initscr();
    signal(SIGWINCH, handle_resize);
    start_color();
    noecho();
    cbreak();
    WINDOW * flags = newwin(22,20,10,5);
    WINDOW* uPM = newwin(30, 25, 6, 25);
    WINDOW* instre = newwin(22, 22, 10, 50);
    refresh();
   
    box(uPM, 0,0);
    mvwprintw(uPM ,14,4, "  _,  _,  _, ._,  ");
    mvwprintw(uPM ,15,4, " (_) |.| (_) |_   ");
    mvwprintw(uPM ,16,4, " (_) |_| (_) ._)  ");
    mvwprintw(uPM ,18,4, "S I M U L A T 0 R");
    char fileName[35];
    
    mvwprintw(uPM ,26,3, "Enter File Name : ");
    mvwprintw(uPM ,27,3, "");
    // mvwscanw(uPM, 26, 4, "Enter File Name : %s", fileName);
    wrefresh(uPM);
    if (argc == 1) takeFileName(uPM, fileName);
    else {
	    strcpy(fileName, argv[1]);
	    FILE *f = fopen(fileName, "r");
	    if (!f) takeFileName(uPM, fileName);
    }

    curs_set(0);
    refresh();
    if(runProgram(flags, uPM, instre,fileName)){
        mvwprintw(uPM ,1,1, " Executed SuccessFully");
    }else{
        mvwprintw(uPM ,1,1, " Execution Error ");
    };
    wrefresh(uPM);
    getch();
    endwin();
    return 0;
}

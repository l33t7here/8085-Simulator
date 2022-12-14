dafault : 
	gcc -o ctui c_tui.c microProcessor.c microProcessor.h  -lcurses
clean: 
	rm  ctui
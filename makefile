dafault : 
	gcc -o ctui c_tui.c microProcessor.c microProcessor.h  -lcurses
run:
	python3 assembler.py $(file)
	./ctui $(patsubst  %.asm,%.hex , $(file))
clean: 
	rm  ctui

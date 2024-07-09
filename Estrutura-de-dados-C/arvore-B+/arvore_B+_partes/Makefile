run-input-1: arvore_B+.exe
	./arvore_B+.exe ../entradas-exemplo/entrada1.txt saida1.txt && rm *.o && rm arvore_B+.exe

run-input-2: arvore_B+.exe
	./arvore_B+.exe ../entradas-exemplo/entrada2.txt saida2.txt && rm *.o && rm arvore_B+.exe

arvore_B+.exe: arvore_B+_main.o arvore_B+_insercao.o arvore_B+_remocao.o arvore_B+_IO.o arvore_B+_formatacao.o
	gcc arvore_B+_main.o arvore_B+_insercao.o arvore_B+_remocao.o arvore_B+_IO.o arvore_B+_formatacao.o -o arvore_B+.exe 

arvore_B+_main.o: arvore_B+_main.c arvore_B+.h
	gcc -c arvore_B+_main.c

arvore_B+_insercao.o: arvore_B+_insercao.c arvore_B+.h
	gcc -c arvore_B+_insercao.c

arvore_B+_remocao.o: arvore_B+_remocao.c arvore_B+.h
	gcc -c arvore_B+_remocao.c

arvore_B+_IO.o: arvore_B+_IO.c arvore_B+.h
	gcc -c arvore_B+_IO.c

arvore_B+_formatacao.o: arvore_B+_formatacao.c arvore_B+.h
	gcc -c arvore_B+_formatacao.c

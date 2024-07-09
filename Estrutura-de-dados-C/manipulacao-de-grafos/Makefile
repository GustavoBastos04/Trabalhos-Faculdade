CFLAGS = -Wall -std=c99

run-mat-2: matriz
	./grafo_matriz.exe ./entradas-exemplo/entrada2.txt saida2Mat.txt
	rm *.o && rm *.exe

run-lis-2: lista
	./grafo_lista.exe ./entradas-exemplo/entrada2.txt saida2Lis.txt
	rm *.o && rm *.exe

run-mat-1: matriz
	./grafo_matriz.exe ./entradas-exemplo/entrada1.txt saida1Mat.txt
	rm *.o && rm *.exe

run-lis-1: lista
	./grafo_lista.exe ./entradas-exemplo/entrada1.txt saida1Lis.txt
	rm *.o && rm *.exe

matriz: CFLAGS+=-DMATRIZ
matriz: grafo_matrizadj.o grafo_aplicacoes_buscas.o
	gcc $(CFLAGS) -o grafo_matriz.exe grafo_matrizadj.o grafo_aplicacoes_buscas.o

grafo_matrizadj.o: grafo_matrizadj.c grafo_matrizadj.h
	gcc $(CFLAGS) -c grafo_matrizadj.c

lista: grafo_listaadj.o grafo_aplicacoes_buscas.o
	gcc $(CFLAGS) -o grafo_lista.exe grafo_listaadj.o grafo_aplicacoes_buscas.o


grafo_listaadj.o: grafo_listaadj.c grafo_listaadj.h
	gcc $(CFLAGS) -c  grafo_listaadj.c 

grafo_aplicacoes_buscas.o: grafo_aplicacoes_buscas.c grafo_matrizadj.h  grafo_listaadj.h
	gcc $(CFLAGS) -c  grafo_aplicacoes_buscas.c 

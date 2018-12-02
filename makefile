COMPACTAR = nome_arquivo.txt

DESCOMPACTAR = nome_arquivo.comp

all: Compacta Descompacta

Compacta: arv_binaria.o lista.o compacta.o
	gcc -o Compacta arv_binaria.o lista.o compacta.o

Descompacta: arv_binaria.o lista.o descompacta.o
	gcc -o Descompacta arv_binaria.o lista.o descompacta.o

arv_binaria.o:
	gcc -c arv_binaria.c

lista.o:
	gcc -c lista.c

compacta.o:
	gcc -c compacta.c

descompacta.o:
	gcc -c descompacta.c

clean:
	del *.o

rmproper: rmpropercomp rmproperdescomp

rmpropercomp: clean
	del Compacta.exe

rmproperdescomp: clean
	del Descompacta.exe

run: runcomp rundescomp

runcomp: Compacta
	Compacta $(COMPACTAR)

rundescomp: Descompacta
	Descompacta $(DESCOMPACTAR)

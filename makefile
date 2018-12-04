### Makefile ###

# Arquivo a compactar
ARQUIVO_COMP = nome_arquivo.txt

#Arquivo a descompactar
ARQUIVO_DESCOMP = nome_arquivo.comp

# Comando para deletar
REMOVER = rm

# Nome do executavel para Compacta
EXECUTAVEL_COMP = Compacta

# Nome do executavel para Descompacta
EXECUTAVEL_DESCOMP = Descompacta

# Comando para executar Compacta
RUN_COMP = ./Compacta

# Comando para executar Descompacta
RUN_DESCOMP = ./Descompacta

### ###

all: $(EXECUTAVEL_COMP) $(EXECUTAVEL_DESCOMP)

$(EXECUTAVEL_COMP): arv_binaria.o lista.o compacta.o
	gcc -o Compacta arv_binaria.o lista.o compacta.o

$(EXECUTAVEL_DESCOMP): arv_binaria.o lista.o descompacta.o
	gcc -o Descompacta arv_binaria.o lista.o descompacta.o

arv_binaria.o: arv_binaria.c
	gcc -c arv_binaria.c

lista.o: lista.c
	gcc -c lista.c

compacta.o: compacta.c
	gcc -c compacta.c

descompacta.o: descompacta.c
	gcc -c descompacta.c

clean:
	$(REMOVER) *.o

rmproper-comp:
	$(REMOVER) $(EXECUTAVEL_COMP) *.o

rmproper-descomp:
	$(REMOVER) $(EXECUTAVEL_DESCOMP) *.o

rmproper:
	$(REMOVER) $(EXECUTAVEL_COMP) $(EXECUTAVEL_DESCOMP) *.o

run-comp: $(EXECUTAVEL_COMP)
	$(RUN_COMP) $(ARQUIVO_COMP)

run-descomp: $(EXECUTAVEL_DESCOMP)
	$(RUN_DESCOMP) $(ARQUIVO_DESCOMP)

run: run-comp run-descomp

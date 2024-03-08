CFLAGS = -Wall -std=c99 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = main.o machines_structure.o 
     
main: main.o machines_structure.o 
	$(CC) -o main main.o machines_structure.o  $(LDFLAGS)

filaNofilaNoticias.o:machines_structure.c
	$(CC) -c $(CFLAGS)machines_structure.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f $(objects) main
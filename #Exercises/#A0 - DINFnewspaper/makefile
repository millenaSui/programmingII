CFLAGS = -Wall -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = jornal.o filaNoticias.o 
     
jornal: jornal.o filaNoticias.o 
	$(CC) -o jornal jornal.o filaNoticias.o  $(LDFLAGS)

filaNofilaNoticias.o:filaNoticias.c
	$(CC) -c $(CFLAGS)filaNoticias.c

jornal.o: jornal.c
	$(CC) -c $(CFLAGS) jornal.c

clean:
	rm -f $(objects) jornal
CC = gcc

# arquivos-objeto
	objects = csvreader.o io.o 
     
csvreader: csvreader.o io.o
	$(CC) -o csvreader csvreader.o io.o $(LDFLAGS)

io.o: io.c
	$(CC) -c $(CFLAGS) io.c

csvreader.o: csvreader.c
	$(CC) -c $(CFLAGS) csvreader.c

clean:
	rm -f $(objects) csvreader
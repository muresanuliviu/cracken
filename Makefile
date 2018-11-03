CC=gcc
CFLAGS=-lssl -lcrypto
EXE_NAME=craken

build: $(EXE_NAME)

$(EXE_NAME): main.c
	$(CC) -o $@ $< $(CFLAGS)

run: $(EXE_NAME)
	./$(EXE_NAME)

clean:
	rm $(EXE_NAME)

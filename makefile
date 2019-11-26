PROG = 5threads

all: $(PROG)

$(PROG): $(PROG).o
	gcc -pthread $(PROG).o -o $(PROG)
$(PROG).o: $(PROG).c
	gcc -c $(PROG).c
clean:
	rm -rf $(PROG)
	rm -rf *.o
run: all
	./$(PROG)

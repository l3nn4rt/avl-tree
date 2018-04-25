dev: AVLtree clean info

info:
	@echo ""
	@echo "  Usage: ./AVLtree [NODE1 NODE2 ...]"
	@echo ""

clean:
	@printf "Removing binaries... "
	@rm -fr bin/
	@echo "Done"

clean-all: clean
	@printf "Removing executable... "
	@rm -f AVLtree
	@echo "Done"
	@echo "All removed."

AVLtree: bin/ bin/main.o bin/tools.o bin/operations.o bin/deque.o bin/print.o
	@printf "Building final executable... "
	@gcc -Wall -o AVLtree bin/main.o bin/tools.o bin/operations.o bin/deque.o bin/print.o
	@echo "Done"

bin/:
	@printf "Making bin/ directory... "
	@mkdir -p bin/
	@echo "Done"

bin/main.o: src/headers.h src/main.c
	@printf "Compiling main... "
	@gcc -c -Wall -o bin/main.o src/main.c
	@echo "Done"

bin/tools.o: src/headers.h src/tools.c
	@printf "Compiling tools... "
	@gcc -c -Wall -o bin/tools.o src/tools.c
	@echo "Done"

bin/operations.o: src/headers.h src/operations.c
	@printf "Compiling operations... "
	@gcc -c -Wall -o bin/operations.o src/operations.c
	@echo "Done"

bin/print.o: src/headers.h src/deque.h src/print.c
	@printf "Compiling print... "
	@gcc -c -Wall -o bin/print.o src/print.c
	@echo "Done"

bin/deque.o: src/deque.h src/deque.c
	@printf "Compiling deque... "
	@gcc -c -Wall -o bin/deque.o src/deque.c
	@echo "Done"


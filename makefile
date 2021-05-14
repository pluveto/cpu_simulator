all:
	gcc main.c -o cpu_simulator.out

oj:
	gcc -E main.c -o cpu_simulator.out
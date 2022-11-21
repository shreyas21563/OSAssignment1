all:
	gcc ls.c -o ls
	gcc date.c -o date
	gcc cat.c -o cat
	gcc mkdir.c -o mkdir
	gcc rm.c -o rm
	gcc fork.c
	./a.out

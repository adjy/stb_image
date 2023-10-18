main	:   main.o image.o
	gcc -o main main.o image.o
	

main.o	:	main.c
	gcc -c -Wall main.c

image.o	:	image.c
	gcc -c -Wall image.c

clean:	
	rm -f image *.o
#make:
exec:  observer.o
	gcc observer.o -o observer

observer.o: observer.c
	gcc -c observer.c

clean:
	rm *.o observer

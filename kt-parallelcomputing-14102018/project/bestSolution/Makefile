
# Gabriel Bronzatti Moro
# gabrielbronzattimoro.es@gmail.com

# FLAGS
FLAGS := -Wall -Wextra -O3 -fopenmp 

# TARGET RULES
all: exec gabarito

gabarito.o: gabarito.c
	gcc $(FLAGS) -o $@ -c $<

gabarito: hpcelo.c gabarito.o
	gcc $(FLAGS) -o $@ $+

exec.o: MatricesMultiplication.c
	gcc $(FLAGS) -o $@ -c $<

exec: hpcelo.c exec.o
	gcc $(FLAGS) -o $@ $+

clean:
	rm -f *.o 
	rm exec gabarito

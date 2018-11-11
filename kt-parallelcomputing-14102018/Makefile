
# Gabriel Bronzatti Moro
# gabrielbronzattimoro.es@gmail.com

# FLAGS
FLAGS := -Wall -Wextra -O2

# TARGET RULES
all: normal_seq normal_par continuos_seq continuos_par tiling_seq tiling_par normal_seqT normal_parT continuos_seqT continuos_parT tiling_seqT tiling_parT

normal_seq.o: normal.c
	gcc $(FLAGS) -o $@ -c $<

normal_seq: hpcelo.c normal_seq.o
	gcc $(FLAGS) -o $@ $+

normal_par.o: normal.c
	gcc $(FLAGS) -fopenmp -o $@ -c $<

normal_par: hpcelo.c normal_par.o
	gcc $(FLAGS) -fopenmp -o $@ $+

continuos_seq.o: continuos.c
	gcc $(FLAGS) -o $@ -c $<

continuos_seq: hpcelo.c continuos_seq.o
	gcc $(FLAGS) -o $@ $+

continuos_par.o: continuos.c
	gcc $(FLAGS) -fopenmp -o $@ -c $<

continuos_par: hpcelo.c continuos_par.o
	gcc $(FLAGS) -fopenmp -o $@ $+

tiling_seq.o: tiling.c
	gcc $(FLAGS) -o $@ -c $<

tiling_seq: hpcelo.c tiling_seq.o
	gcc $(FLAGS) -o $@ $+

tiling_par.o: tiling.c
	gcc $(FLAGS) -fopenmp -o $@ -c $<

tiling_par: hpcelo.c tiling_par.o
	gcc $(FLAGS) -fopenmp -o $@ $+

normal_seqT.o: normalT.c
	gcc $(FLAGS) -o $@ -c $<

normal_seqT: hpcelo.c normal_seqT.o
	gcc $(FLAGS) -o $@ $+

normal_parT.o: normalT.c
	gcc $(FLAGS) -fopenmp -o $@ -c $<

normal_parT: hpcelo.c normal_parT.o
	gcc $(FLAGS) -fopenmp -o $@ $+

continuos_seqT.o: continuosT.c
	gcc $(FLAGS) -o $@ -c $<

continuos_seqT: hpcelo.c continuos_seqT.o
	gcc $(FLAGS) -o $@ $+

continuos_parT.o: continuosT.c
	gcc $(FLAGS) -fopenmp -o $@ -c $<

continuos_parT: hpcelo.c continuos_parT.o
	gcc $(FLAGS) -fopenmp -o $@ $+

tiling_seqT.o: tilingT.c
	gcc $(FLAGS) -o $@ -c $<

tiling_seqT: hpcelo.c tiling_seqT.o
	gcc $(FLAGS) -o $@ $+

tiling_parT.o: tilingT.c
	gcc $(FLAGS) -fopenmp -o $@ -c $<

tiling_parT: hpcelo.c tiling_parT.o
	gcc $(FLAGS) -fopenmp -o $@ $+

clean:
	rm -f *.o 
	rm normal_seq normal_par continuos_seq continuos_par tiling_seq tiling_par normal_seqT normal_parT continuos_seqT continuos_parT tiling_seqT tiling_parT

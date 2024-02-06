run:
	@gcc -o gsl_optimise.out gsl_optimise.c -lgsl -lgslcblas -lm
	@./gsl_optimise.out

val:
	@gcc -g -o gcl_optimise_val.out gcl_optimise.c
	@valgrind --leak-check=full ./gcl_optimise_val.out

gdb:
	@gcc gcl_optimise.c -o gcl_optimise_gdb.out -g
	@gdb gcl_optimise_gdb.out

clean:
	@rm -f *.out
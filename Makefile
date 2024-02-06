run:
	@gcc -o jk_resample.out jk_resample.c -lgsl -lgslcblas -lm
	@./jk_resample.out

val:
	@gcc -g -o jk_resample_val.out jk_resample.c
	@valgrind --leak-check=full ./jk_resample_val.out

gdb:
	@gcc jk_resample.c -o jk_resample_gdb.out -g
	@gdb jk_resample_gdb.out

clean:
	@rm -f *.out

 
kompilator=g++
standard=-std=c++14
optymalizacja=-O3
# optymalizacja=
# debug=-g
debug=
leaks=../../../memory-leaks


__ : main
	./main   
#	./main -i test.txt -o test.out -r 0.8 -w 0.2 -k 4 -p 5
	./main -i test.txt -o test.out -r 0.51 -w 0.49 -k 4 -p 10
	   	   
main : main.o Chromosome.o Population.o Darwin.o  FitFunction.o  debug_new.o static_mem_pool.o mem_pool_base.o bool_array.o
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -o $@ $^ 
	            
main.o : main.cpp 
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -c -o $@ $^ 
	
Chromosome.o : Chromosome.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -c -o $@ $^ 		
		
Population.o : Population.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -c -o $@ $^ 		
		
Darwin.o : Darwin.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -c -o $@ $^ 		
FitFunction.o : FitFunction.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -c -o $@ $^ 		

		
	# kompilacja biblioteki wykrywajacej wycieki pamieci		
debug_new.o : $(leaks)/debug_new.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 
	
static_mem_pool.o : $(leaks)/static_mem_pool.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 		

mem_pool_base.o : $(leaks)/mem_pool_base.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 		

bool_array.o : $(leaks)/bool_array.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 	
	
clear :
	rm *.o
	rm main	
	
	
doxy : 
	doxygen Doxyfile
	


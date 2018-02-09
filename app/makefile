
 
kompilator=g++
standard=-std=c++14
optymalizacja=-O3
# optymalizacja=
# debug=-g
debug=


__ : main
	./main   
	   	   
main : main.o Chromosome.o Population.o Darwin.o  FitFunction.o 
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

clear :
	rm *.o
	rm main	

# PrimesContainer 
## 1 is not prime!
## Build  
  *application:*  
  **make -f Makefile-1**  
  *unitTests*  
  **make -f Makefile-2**    
## Run  
   *Start with default settings:*  
    **./PrimeContainerApp**  
   *Start tests:*    
    **./TestApp**  
### Settings flags
   **-q [value]** using container by quantity of primes  
   **-m [value]** using container with upper bound   
   **-f [filepath]** output file  
   **-s** outputs only super-primes numbers  
   **-j** outputs only Sophie Germain primes  
   
   **Default settings are equal to this flag set:  -m 100**  
 ## Flag sets examples  
   **./PrimeContainerApp**
   **./PrimeContainerApp -m 1000 -f test.txt**  
   **./PrimeContainerApp -q 1000 -f test.txt -s**  

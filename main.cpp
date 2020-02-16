#include <fstream>
#include <cstdint>
#include <iostream>
#include <unistd.h>
#include "primes.h"




/*!
    Лямбда - функция, проверяющая число на принадлежность к последовательености простых чисел Софи Жермен
    \param value простое число
    \returns true если принадлежит, иначе false.
*/
auto sofi = [](uint32_t value){
                            for (int j = 2; j < (int)sqrt(value * 2 + 1) + 1;j++)
                                if ((value*2 + 1) % j == 0)
                                    return false;
                            return true;
                            };





/*!
    Лямбда - функция, проверяющая число на принадлежность к последовательености Суперпростых чисел 
    \param i позиция числа в ряду контейнера
    \returns true если принадлежит, иначе false.
    \warning в контейнере нумерация начинается с нуля, нумерация в последовательности с единицы
*/
auto super =  [](uint32_t i){
                        if (i+1 == 1)
                            return false;
                        for (int j = 2; j < (int)sqrt(i+1) + 1;j++)
                            if ((i+1) % j == 0)
                                return false;
                        return true;
                      }; 




/*!
    \brief Структура, хранящая в себе данные полученные с команндной строки            
*/
typedef struct 
{
    char type = '0';
    long long value = 100;
    std::string file = "";
    char sequence = '0';
}cmdParsedData;



int main (int argc, char *argv[])
{
    int opt;
    Primes* primeContainer = nullptr;
    cmdParsedData cmdParse;
    while((opt = getopt(argc, argv, "q:f:m:js?")) != -1)  
    {  
        switch(opt)  
        {  
            case 'q':   
                cmdParse.type = 'q';
                cmdParse.value  = std::atoll(optarg);
                break; 
            case 'm':   
                cmdParse.type = 'm';
                cmdParse.value  = std::atoll(optarg);
                break;  
            case 'f':
                cmdParse.file = std::string(optarg); 
                break;
            case 'j':
                cmdParse.sequence = 'j';
                break;
            case 's':
                cmdParse.sequence = 's';
                break;  
            case '?': 
                break;  
        }  
    } 
    if (cmdParse.value < 0)
    {
        std::cout << " Negative parameters for -q or -m is forbidden" << std::endl;
        getchar();
        return 0;
    }
	std::cout << "Application started" << std::endl << std::endl;
    try
    {
        if (cmdParse.type == 'q')
        {
            primeContainer = new Primes(cmdParse.value,Primes::UNLIMITED);
            std::cout << "A container is created using the constructor with a parameter by quantity and a special flag " << std::endl  << std::endl;
        }
        else
        {
            if(cmdParse.type == 'm')
            {
                primeContainer = new Primes(cmdParse.value);
                std::cout << "A container is created using the constructor with a parameter along the upper boundary " << std::endl << std::endl;
            }
            else
            {
                primeContainer = new Primes;
                std::cout << "A container is created using the default constructor " << std::endl;
            }    
        }
    }catch(std::bad_alloc &e)
    {
        std::cout << "\tMemory allocation error\n\tPlease try again with smaller agrument for -q/-m key\n" << std::endl;
        getchar();
        return 0;
    }
    std::cout << "Container created successfully, quantity of primes: " << primeContainer->size() <<  std::endl << std::endl;;    
    if (cmdParse.file != "")
    {
        std::ofstream outputFileHandler;
        outputFileHandler.open(cmdParse.file);
        if (!outputFileHandler.is_open())
        {
            std::cout << "\tUnable to open file! ";
            getchar();
            return 0;
        }
        std::cout << "Output file " << cmdParse.file <<" successfully opened " <<  std::endl << std::endl;;    
        for (size_t i = 0; i < primeContainer->size(); i++)
            if (cmdParse.sequence == 'j')
            {
                if (sofi((*primeContainer)[i]))
                    outputFileHandler << (*primeContainer)[i] << std::endl;
            }
            else
            {
                if (cmdParse.sequence == 's')
                {
                    if (super(i))
                        outputFileHandler << (*primeContainer)[i] << std::endl;
                }
                else
                    outputFileHandler << (*primeContainer)[i] << std::endl;       
            }
        outputFileHandler.close();
        std::cout << "Writing has already finished. File has been closed" << std::endl;
    }
    else
    {
        std::cout << "Elements of container : " <<  std::endl << std::endl;;   
        for (size_t i = 0; i < primeContainer->size(); i++)
            if (cmdParse.sequence == 'j')
            {
                if (sofi((*primeContainer)[i]))
                    std::cout << (*primeContainer)[i] << " ";
            }
            else
            {
                if (cmdParse.sequence == 's')
                {
                    if (super(i))
                       std::cout << (*primeContainer)[i] << " ";
                }
                else
                    std::cout << (*primeContainer)[i] << " ";       
            }  
    }
    std::cout << std::endl << "Press something to exit" << std::endl;
    getchar();
    return 0;
}
#include "primes.h"


Primes::Primes()
{
    this->EratosfenesAlgorithm(100);
}
Primes::Primes(uint32_t max)
{   
    if (max != 0)
        this->EratosfenesAlgorithm(max);
}
Primes::Primes(uint32_t quantity, ContainerType type):typeFlag(UNLIMITED)
{
    if (quantity == 0)
        return;
    this->containerData = new uint32_t[quantity];
    for (size_t i = 0 ,j = 1;i < quantity;j++)
        if(isPrime(j))
            this->containerData[i++] = j;
    this->length = quantity;  
}
Primes::Primes(const Primes& other):
        length(other.length),
        typeFlag(other.typeFlag),
            containerData(new uint32_t[other.length])
{
    for (size_t i = 0; i < other.length ; i++)
        this->containerData[i] = other.containerData[i];
}
Primes::Primes(Primes&& other)
                :containerData(other.containerData),
                length(other.length),
                typeFlag(other.typeFlag)
{   
    other.containerData = nullptr;
    other.length = 0;
    other.typeFlag = false;
}
void Primes::operator=(const Primes& other)
{
    if (&other == this)
        return ;
    delete [] this->containerData;
    this->length = other.length;
    this->typeFlag = other.typeFlag;
    this->containerData = new uint32_t[this->length];
    for (size_t i = 0; i < this->length ; i++)
        this->containerData[i] = other.containerData[i];
}
void Primes::operator=(Primes&& other)
{
    delete [] this->containerData;
    this->containerData = other.containerData;
    this->length = other.length;
    this->typeFlag = other.typeFlag;
    other.length = 0;
    other.typeFlag = false;
    other.containerData = nullptr;
}
uint32_t Primes::operator[](uint32_t index)
{
    if (index >= this->length)
        throw std::out_of_range("Out of range");
    return this->containerData[index];
}

Primes::~Primes()
{
    delete [] this->containerData;
    this->containerData = nullptr;
}
Primes::Iterator::Iterator(uint32_t* pointer)
{
    this->pointer = pointer;
}
inline Primes::Iterator& Primes::Iterator::operator++()
{
    this->pointer++;
	return *this;
}
inline uint32_t Primes::Iterator::operator*()
{
	return *this->pointer;
}
inline bool Primes::Iterator::operator==(const Iterator& other)
{
    return this->pointer == other.pointer;
}
inline bool Primes::Iterator::operator!=(const Iterator& other)
{
    return !(this->pointer == other.pointer);
}


Primes::Iterator Primes::begin()
{
    return Iterator(this->containerData);
}
Primes::Iterator Primes::end()
{
    if (this->typeFlag == UNLIMITED)
        return Iterator(nullptr);
    return Iterator(this->containerData + this->length);
}






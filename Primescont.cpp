#include <cmath>
#include <vector>

class Primes
{
    private:
        typedef const bool ContainerType;
        uint32_t* containerData = nullptr;
        uint32_t length = 0;
        bool typeFlag = true;
        void EratosfenesAlgorithm(uint32_t max) 
        {
            std::vector<bool> isPrimeArray(max + 1 , true);
            for (size_t i = 2;i < isPrimeArray.size();i++)
            if (isPrimeArray[i] == true)
            {
                for (size_t j = i*i;j < isPrimeArray.size();j+=i)
                    isPrimeArray[j] = false;
                this->length++;
            }
            this->containerData = new uint32_t[this->length];
            for(size_t i = 2 ,j = 0; i < max + 1 ;i++)
                if (isPrimeArray[i] == true)
                    this->containerData[j++] = i;
        }
        static bool isPrime(uint32_t value)
        {
            if (value < 2)
                return false;
            for (int i = 2; i < (int)sqrt(value) + 1;i++)
                if (value % i == 0)
                    return false;
            return true;
        }
    public:
        static Primes::ContainerType UNLIMITED = false;
        explicit Primes(uint32_t max);
        explicit Primes();
        explicit Primes(uint32_t quantity, ContainerType type);
        explicit Primes(const Primes& other);
        explicit Primes(Primes&& other);
};
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

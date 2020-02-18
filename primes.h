#include <cmath>
#include <vector>
#include <cstdint>
#include <stdexcept>




/*!
	\brief Класс - контейнер простых чисел 
    \author Агафонов Алексей Сергеевич
	Данный класс реализует интерфейс позволяющий работать с простыми числами 
    \warning Единица не простое число -> в контейнере не содержится!
*/
class Primes
{
    private:
        typedef const bool ContainerType;
        uint32_t* containerData = nullptr;
        uint32_t length = 0;
        bool typeFlag = true;
        /*! 
            Метод заполняет контейнер простыми числами до верхней границы. 
            Применяется алгоритм: Решето Эратосфера 
            Сложность данного алгоритма O(nlog(log(n))), что позволяется быстро находить все  
            простые числа до заданного 
            \param max верхняя граница
        */
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
        /*!
            Статический метод - предикат проверяющий произвольное число на простоту
            \param value число, которое необходимо проверить
            \returns true если число простое, иначе false
        */
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
        friend class UnitTest;
        static Primes::ContainerType UNLIMITED = false;
        /*!
            Конструктор с верхней границей. Инициализирует контейнер с верхней границей (1 ... max)
            \param max верхняя граница простых чисел
        */
        explicit Primes(uint32_t max);
        /*!
            Конструктор по умоланию. Инициализирует контейнер состоящий из простых чисел до 100
        */
        explicit Primes();
        /*!
            Конструктор с заданием количества простых чисел . Инициализирует контейнер состоящий из quantity элементов
            \param quantity количество простых чисел
            \param type флаг определяющий создание контейнера именно по количеству
        */
        explicit Primes(uint32_t quantity, ContainerType type);
        /*!
            Конструктор копирования. Инициализирует контейнер являющийся полной копией контейнера, преданного в качестве аргумента
            \param other контейнер, копию которого хотим создать
        */
        explicit Primes(const Primes& other);
        /*!
            Конструктор перемещения. Используется семантика перемещения.
            \param other контейнер, содержимое которого хотим переместить
        */
        explicit Primes(Primes&& other);
        /*!
            Оператор копирующего присваивания. Метод делает текущий контейнер полной копией контейнера, преданного в качестве аргумента
            \param other контейнер, копию которого хотим создать
        */
        void operator=(const Primes& other);
        /*!
            Оператор перемещающего присваивания. Используется семантика перемещения.
            \param other контейнер, содержимое которого хотим переместить
        */
        void operator=(Primes&& other);
        /*! 
            \returns  Итератор на начало контейнера
        */
        /*!
            \brief Класс - итератора.
            Элементы данного класса позволяют интерироваться по контейнеру
            \author Агафонов Алексей Сергеевич
            
        */
        class Iterator{
            private:
                uint32_t* pointer;
            public:
		friend class UnitTest;
                /*! 
                    Конструктор, инициализирующий интератор на указанный элемент
                    \param pointer указатель на элемент 
                */
                Iterator(uint32_t* pointer);
                /*!
                    Оператор инкремента. Метод перемещающий итератор на один элемент вперед.
                    \warning используется инфексная запись ex: ++iter;
                */
                Iterator& operator++();
                /*!
                    Оператор разыменования. Метод позволяет получить текущий элемент контейнера.
                    \returns Текущий элемент контейнера
                */
                uint32_t operator*();
                /*!
                    Оператор проверки на равенство. Метод проверяет совпадают ли указатели на элементы контейнера.
                    \returns true если укзатели совпали, иначе false
                */
                bool operator==(const Iterator& other);
                /*!
                    Оператор проверки на нуравенство. Метод проверяет различны ли указатели на элементы контейнера.
                    \returns true если укзатели не совпали, иначе false
                */
                bool operator!=(const Iterator& other);
        };
        Iterator begin();
        /*! 
            Метод возвращает итератор на конец контейнера.Для контейнера без верхней границы end() достижим только в пустом контейнере.
            \returns Итератор на конец контейнера
        */
        Iterator end();
        /*! 
            \returns Количество простых чисел в контейнере.
        */
        uint32_t size() { return this->length;};
        /*!
            Оператор индексации. Метод делает текущий контейнер полной копией контейнера, преданного в качестве аргумента
            \param index Индекс элемента 
            \throw std::out_of_range 
            \returns Элемент контейнера с индексом index
        */
        uint32_t operator[](uint32_t index); 
        /*!
            Деструктор. Освобождает память из-под контейнера.
        */
        ~Primes();
};

#include<iostream>
#include <cassert>
#include "primes.h"

class UnitTest {
	public:
		static void startAllTests();
		static void defaultConstructorTEST();
		static void maxConstructorTEST();
		static void quantityConstructorTEST();
		static void copyConstructorTEST();
        static void moveConstructorTEST();
		static void beginTEST();
		static void endTEST();
		static void sizeTEST();
		static void copyOperatorTEST();
        static void moveOperatorTEST();
		static void indexOperatorTEST();
};
void UnitTest::startAllTests()
{
    	defaultConstructorTEST();
	maxConstructorTEST();
	quantityConstructorTEST();
	copyConstructorTEST();
    	moveConstructorTEST();
	beginTEST();
	endTEST();
	sizeTEST();
	copyOperatorTEST();
    	moveOperatorTEST();
	indexOperatorTEST();
    std::cout << "All test successfully passed!" << std::endl;
}
void UnitTest::defaultConstructorTEST()
{
	Primes pr;
	assert(25 == pr.length);	
    assert(pr.typeFlag == true);
    assert(pr.containerData!=nullptr);
}
void UnitTest::maxConstructorTEST()
{
    Primes pr(300);	
    Primes pr1(0);
    assert(pr.typeFlag == true);
    assert(pr.containerData != nullptr);
    assert(pr1.length == 0);
    assert(pr1.containerData == nullptr);
}
void UnitTest::quantityConstructorTEST()
{
    Primes pr(100,Primes::UNLIMITED);
    assert(pr.containerData != nullptr);
    assert(pr.length == 100);
    assert(pr.typeFlag == Primes::UNLIMITED);
}
void UnitTest::copyConstructorTEST()
{
    Primes pr1(0,Primes::UNLIMITED);
    Primes pr2(pr1);
    assert(pr1.containerData != pr2.containerData);
    assert(pr1.length == pr2.length);
    assert(pr1.typeFlag == pr2.typeFlag);
}
void UnitTest::moveConstructorTEST()
{
    Primes pr1(50);
    Primes pr2(pr1);
    pr1 = pr2;
    assert(pr1.containerData != pr2.containerData);
    assert(pr1.length == pr2.length);
    assert(pr1.typeFlag == pr2.typeFlag);
}
void UnitTest::copyOperatorTEST()
{
    Primes pr1(50,Primes::UNLIMITED);
    Primes pr2(std::move(pr1));
    assert(pr1.containerData == nullptr);
    assert(pr1.length == 0);
    assert(pr1.typeFlag == false);
    assert(pr2.containerData != nullptr);
    assert(pr2.length == 50);
    assert(pr2.typeFlag == false);
}
void UnitTest::moveOperatorTEST()
{
    Primes pr1(50,Primes::UNLIMITED);
    Primes pr2(10,Primes::UNLIMITED);
    pr2 = std::move(pr1);
    assert(pr1.containerData == nullptr);
    assert(pr1.length == 0);
    assert(pr1.typeFlag == false);
    assert(pr2.containerData != nullptr);
    assert(pr2.length == 50);
    assert(pr2.typeFlag == false);
}
void UnitTest::beginTEST()
{
    Primes pr1;
    assert(pr1.begin().pointer != nullptr);
    assert(pr1.begin().pointer == pr1.containerData);
}
void UnitTest::endTEST()
{
    Primes pr1;    
    Primes pr2(0,Primes::UNLIMITED);
    //assert(pr1.end() == Primes::Iterator(pr1.containerData + pr1.length));
    //assert(pr2.end() == Primes::Iterator(nullptr));
}
void UnitTest::sizeTEST()
{
    Primes pr1(100,Primes::UNLIMITED);
    assert(pr1.length == pr1.size());
}
void UnitTest::indexOperatorTEST()
{
    Primes pr1(100,Primes::UNLIMITED);
    assert(pr1.containerData[30] == pr1[30]);
}
int main(int argc, char* argv[])
{
	UnitTest::startAllTests();
    std::cout << std::endl << "press something to exit" << std::endl;
    getchar();
}

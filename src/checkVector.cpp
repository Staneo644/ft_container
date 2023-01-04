#include "vector.hpp"
#include <vector>
#include <iterator>



template <class InputIterator>
void printm(ft::vector<InputIterator> numbers){
    std::cout << std::endl;
    std::cout << "My Vector" << std::endl;
    for (std::size_t i = 0; i < numbers.size(); i++){
        std::cout << numbers[i] << "    ";
    }
}

template <class InputIterator>
void prints(std::vector<InputIterator> numbers){

    std::cout << "Normal Vector" << std::endl;
    for (std::size_t i = 0; i < numbers.size(); i++){

        std::cout << numbers[i] << "    ";
    }
    std::cout << std::endl;
}

template <class InputIterator>
void print(std::vector<InputIterator> stvec, ft::vector<InputIterator> myvec, std::string myString){
    std::cout << std::endl << std::endl <<std::endl << "********* "<< myString <<" *********" << std::endl;
    prints(stvec);
    printm(myvec);
    std::cout << std::endl << "*************************************" << std::endl << std::endl;
}

template <class InputIterator>
void printOneValue(InputIterator stvec, InputIterator myvec, std::string myString){
    std::cout << std::endl << std::endl <<std::endl << "********* "<< myString <<" *********" << std::endl;
    std::cout << "Normal Vector : " << stvec << std::endl;
    std::cout << "My Vector : " << myvec << std::endl;
    std::cout << std::endl << "*************************************" << std::endl ;//<< std::endl;
}


void testVector(){
    std::vector<int> stvec( 5, 4);
    ft::vector<int> myvec( 5, 4);
    print(stvec, myvec, "Create element");

    {


        std::vector<int> stvecit(stvec.begin(), stvec.end() - 2);
        ft::vector<int> myvecit(myvec.begin(), myvec.end() - 2);

        print(stvecit, myvecit, "Create element with iterator");
    }
    myvec[2] = 3;
    stvec[2] = 3;
    print(stvec, myvec, "Set my value");

    myvec.resize(8);
    stvec.resize(8);
    print(stvec, myvec, "increase the size");

    myvec.resize(3);
    stvec.resize(3);
    print(stvec, myvec, "Decrement the size");

    myvec.push_back(35);
    stvec.push_back(35);
    print(stvec, myvec, "pushback");

    myvec.pop_back();
    stvec.pop_back();
    print(stvec, myvec, "popback");

    printOneValue(stvec.front(), myvec.front(), "front");
    printOneValue(stvec.back(), myvec.back(), "back");

    ////////////
    for (int i=1; i<=10; i++) myvec.push_back(i);
    for (int i=1; i<=10; i++) stvec.push_back(i);

    ft::vector<int>::iterator myIt = myvec.end() - 1;
    std::vector<int>::iterator stIt = stvec.end() - 1;

    printOneValue(*stvec.erase(stIt), *myvec.erase(myIt), "ValueErase");
    print(stvec, myvec, "Erase");
    ////////////

    ////////////
    myIt = myvec.end() ;
    stIt = stvec.end() ;

    printOneValue(*stvec.erase(stIt - 3, stIt), *myvec.erase(myIt - 3, myIt), "Value iterator Erase");
    print(stvec, myvec, "Erase Iterator");
    ////////////


    myIt = myvec.end() - 3 ;
    stIt = stvec.end() - 3;

    printOneValue(*stvec.insert(stIt,  7), *myvec.insert(myIt, 7), "Value iterator Insert");
    print(stvec, myvec, "Insert Iterator");


    stvec.insert(stIt - 3,4,  9);
    myvec.insert(myIt - 3,4, 9);
    print(stvec, myvec, "Insert Iterator many call");

    std::vector<int>::iterator anOtherVector = std::vector<int>(5,88).begin();

    stvec.insert(stIt - 5, anOtherVector, anOtherVector + 2);
    myvec.insert(myIt - 5, anOtherVector, anOtherVector + 2);
    print(stvec, myvec, "Insert Iterator many call");

    ft::vector<int> mynewvec(5,88);
    std::vector<int> stnewvec(5,88);

    myvec.swap(mynewvec);
    stvec.swap(stnewvec);
    print(stvec, myvec, "Iterator swaped");
    print(stnewvec, mynewvec, "Iterotar who was swap");

}


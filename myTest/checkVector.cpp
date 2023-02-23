#include "../src/main.hpp"

void printOneValue(ft::vector<value>::iterator a, std::string str){
   
    std::cout << "Vector " << str << " : ";
 
    std::cout << *a << "  ";
    std::cout << std::endl << std::endl;
}

void printv(ft::vector<value> a, std::string str){
    print<ft::vector<value>::iterator>(a.begin(), a.end(), str, _vector);
}

void printOneValuev(ft::vector<value>::iterator a, std::string str){
    printOneValue(a, str);
}

void checkVector(){
    ft::vector<value> myvec( 5, 4);
    printv(myvec, "Create container");

    myvec[2] = 3;

    printv( myvec, "Set my value");

    myvec.resize(8);

    printv(myvec, "increase the size");

    myvec.resize(3);

    printv(myvec, "Decrement the size");

    myvec.push_back(35);

    printv(myvec, "pushback");

    myvec.pop_back();

    printv(myvec, "popback");

    myvec.resize(15, 8);

    printv(myvec, "resize");

    std::cout << "size : "<< myvec.size() << ", max size : " << myvec.max_size() << "\n\n";
    for (int i=1; i<=10; i++) myvec.push_back(i);

    ft::vector<int>::iterator myIt = myvec.end() - 1;

    printv(myvec, "Erase");

    myIt = myvec.end() ;

    printOneValuev(myvec.erase(myIt - 3, myIt), "Value iterator Erase");
    printv( myvec, "Erase Iterator");

    myIt = myvec.end() - 3 ;

    printOneValuev(myvec.insert(myIt, 7), "Value iterator Insert");
    printv( myvec, "Insert Iterator");

    myvec.insert(myIt - 3,4, 9);
    printv( myvec, "Insert Iterator many call");

    ft::vector<value>::iterator anOtherVector = ft::vector<value>(5,88).begin();
 
    myvec.insert(myIt - 5, anOtherVector, anOtherVector + 2);
    printv(myvec, "Insert Iterator many call");

    ft::vector<value> mynewvec(5,88);


    myvec.swap(mynewvec);
  
    printv(myvec, "After swap");
    printv(mynewvec, "vector who was swap");

    int a = 4;
    ft::vector<int> testIsIntegral(a, a + 1);
    printv(testIsIntegral, "Check is-integral");

}


#include "../src/main.hpp"

void printOneValues(ft::stack<value> a, std::string str){
    std::cout << "Stack " << str << " : ";
    std::cout << a.top() << "  ";
    std::cout << std::endl << std::endl;

}



void checkStack(){
    ft::stack<value>	ctnr;
	ctnr.push(21);
	ctnr.push(42);
	ctnr.push(1337);
    printOneValues(ctnr, "After push-back");

	ft::stack<value>		stck(ctnr);

	std::cout << "empty: " << stck.empty() << std::endl << std::endl;
	std::cout << "size: " << stck.size() << std::endl << std::endl;

    ft::stack<value>        si(ctnr);
    printOneValues(si, "Copy construct");
	stck.pop();
    printOneValues(stck, "delete element");
    return ;
}
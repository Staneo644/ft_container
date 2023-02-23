#include "../src/main.hpp"

void printm(ft::map<value, key> a, std::string str){
    print<ft::map<value, key>::iterator>(a.begin(), a.end(), str);
}

void printOneValuem(ft::map<value, key>::iterator a, std::string str){
    printOneValue<ft::map<value, key>::iterator>(a, str);
}


void checkMap(){
	ft::map<value,key> mymap;

	printm(mymap, "Initialise");
	mymap[5]=300;
	mymap[5]=400;
	mymap[6]=400;
	printm(mymap, "Put the same value");
	ft::pair<value,key>mypair;
	mymap.value_comp();

	mymap.insert(ft::make_pair<value,key>(4,5));
	mymap.insert(ft::make_pair<value,key>(6,5));
	printm(mymap, "Insert pair");

	mymap.erase(12);
	mymap.erase(4);
	printm(mymap, "Erase");

	std::cout << "size : " << mymap.size() << "\n\n";

	printOneValuem(mymap.find(5), "Find");
	printOneValuem(--mymap.end(), "End - 1");

	std::cout << "Map :\nEqual range : "<< mymap.equal_range(5).first->first << " - " <<  mymap.equal_range(5).second->first << std::endl << std::endl;
    ft::map<value, key> comp(mymap);

	std::cout << "Map :\nEqual operator : "<< (mymap == comp)  << std::endl << std::endl;
	std::cout << "Map :\nSuperiority operator : "<< (mymap > comp)  << std::endl << std::endl;
    mymap[45] = 510;
	std::cout << "Map :\nSuperiority operator : "<< (mymap > comp) << std::endl << std::endl;
	std::cout << "Map :\nEqual operator : "<< (mymap == comp)  << std::endl << std::endl;

    comp[2] = 1;
    comp[3] = 1;
    comp[4] = 11;
    comp[5] = 1;
	comp[6] = 5;
	comp[7] = 5;
	comp[8] = 5;
    comp[11] = 7;
    comp[12] = 7;
    comp[15] = 7;
	comp[16] = 5;
    comp[14] = 7;
    comp[13] = 7;
	comp[17] = 5;
	comp[18] = 5;
	mymap.clear();
	printm(mymap, "After clear");
}
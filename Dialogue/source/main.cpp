#include <Cocktail/Cocktail.h>
#include "Bar/Bar.h"
#include <iostream>

using namespace Lab2;

int main(){
    try {
        Cocktail a("Cock", 100, 10);
        //std::cin >> a;
        std::cout << a;
        //Bar huy = Bar(10);
        //std::cout << huy;
        //unsigned count = huy.empty();
        //std::cout << count <<std::endl;
        Bar test(0);
        test.input();
        std::cout << test["a"].get_name() <<std::endl;
        test += a;
        std::cout << test << std::endl;
        Cocktail cocktails[3];
        cocktails[0] = Cocktail("Cocktail1", 500, 8.0);
        cocktails[1] = Cocktail("Cocktail2", 250, 12.0);
        cocktails[2] = Cocktail("Cocktail3", 250, 10.0);

        Bar bar(3, 3, cocktails);
        std::cout << bar.find_degree(10, 12);

//        test.calculate_volume(2);
//      test.change_name(a.get_name(), "ok");
//    test.remove("a");
    }
    catch(const std::bad_alloc& ba) {
        std::cerr << "Not enough memory" << std::endl;
        //erase(matrix);
        return 1;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        //erase(matrix);
        return 1;
    }
    return 0;
}
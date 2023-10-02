#ifndef OOP_LAB2_GET_NUM_H
#define OOP_LAB2_GET_NUM_H
#include <cstring>
#include <iostream>
#include <limits>

namespace Get {
    template<class T>
    T get_num(std::istream &in, T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max()) {
        T a;
        while (true) {
            in >> a;
            if (in.eof())     //end of file
                throw std::runtime_error("Failed to read number: EOF");
            else if (in.bad())
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
            else if (in.fail()) {
                in.clear();               //clear cin
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong; repeat please!" << std::endl;
            } else if (a >= min && a <= max)
                return a;
            else std::cout << "Repeat!!";
        }
    }
}

#endif

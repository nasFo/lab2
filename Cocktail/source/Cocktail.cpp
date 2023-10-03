#include "Cocktail/Cocktail.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <Utils/get_num.h>

using namespace Get;

namespace Lab2{

    Cocktail::Cocktail(std::string name, unsigned volume, double degree): name_ {std::move(name)}, volume_ {volume}, degree_ {degree}
    {
        if(degree < 0 || degree > 100)
            throw std::invalid_argument("invalid degree");
    }

    Cocktail &Cocktail::set_name(const std::string &name)
    {
        this->name_ = name;
        return *this;
    }

    Cocktail& Cocktail::set_volume(unsigned volume) {
        volume_ = volume;
        return *this;
    }

    Cocktail &Cocktail::set_degree(double degree) {
        if(degree < 0 || degree > 100)
            throw std::invalid_argument("invalid degree");
        degree_ = degree;
        return *this;
    }

    Cocktail& Cocktail:: operator +(const Cocktail& second){
        if (this == &second) return (*this);
        //Cocktail res;
        name_ += "+" + second.name_;
        volume_ += second.volume_;
        degree_ = (degree_ + second.degree_) / 2;
        return *this;
    }

    Cocktail &Cocktail:: operator =(const Cocktail& second){
        if (this == &second) return *this;
        name_ = second.name_;
        volume_ = second.volume_;
        degree_ = second.degree_;
        return *this;
    }

    Cocktail& Cocktail:: operator >(Cocktail& second){
        const unsigned pour_volume_ = 100;
        size_t v = std::min(pour_volume_, second.volume_);
        volume_ += v;
        second.volume_ -= v;
        degree_ = (degree_ + second.degree_) / 2;
        return *this;
    }

    Cocktail &Cocktail:: operator *(int num){
        volume_ *= num;
        return *this;
    }

    std::ostream & operator <<(std::ostream &out, const Cocktail &a){
        const std::string& name = a.get_name();
        unsigned volume = a.get_volume();
        double degree = a.get_degree();
        out << name << " "<< volume<< " " << degree << std::endl;
        return out;
    }


    std::istream & operator >>(std::istream &in, Cocktail &a)
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string name;
        getline(in, name);
        a.set_name(name);
        a.set_volume(get_num(in,0));
        a.set_degree(get_num(in,0,100));
        return in;
   }

    Cocktail &Cocktail:: pour(Cocktail& second, unsigned volume){
        volume_ += volume;
        second.volume_ -= volume;
        degree_ = (degree_ + second.degree_) / 2;
        return *this;
    }
}

#include "Bar/Bar.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <Utils/get_num.h>
#include <Cocktail/Cocktail.h>

using namespace Get;

namespace Lab2{

    Bar:: ~Bar()
    {
        delete [] card_;
        delete [] volume_degree;
    }


    Bar::Bar(unsigned m_size) : size_ {0},
                                m_size_ {m_size},
                                card_(new Cocktail [m_size_]){
        try {
            volume_degree = new unsigned[4]{0, 0, 0, 0};
        }
        catch (std::bad_alloc& e) {
            delete [] card_;
            throw;
        }
    }

    Bar::Bar(Bar &&st) noexcept: Bar()
    {
        swap_bar(st);
    }

    Bar::Bar(const Bar &st) : Bar(st.m_size_, st.m_size_, st.card_) {}

    void Bar::remove(const std::string& str)
    {
        Cocktail& to_remove = (*this)[str];
        if (to_remove.get_volume() == 0)
            throw std::runtime_error("Cocktail isn't exist!");
        (to_remove).set_volume(0);
        size_ -= 1;
        define_degree(to_remove.get_degree()) -= to_remove.get_volume();
    }

    Bar& Bar::change_name(const std::string& old_name, const std::string& new_name)
    {
        Cocktail& to_change = (*this)[old_name];
        if (to_change.get_volume() == 0)
            throw std::runtime_error("Cocktail isn't exist!");
        to_change.set_name(new_name);
        return *this;
    }

    Bar::Statement Bar::empty() const
    {
        if (size_ == 0)
            return Statement::EMPTY;
        else if (size_ == m_size_)
            return Statement::FULL;
        else
            return Statement::SEMI_FULL;
    }

    unsigned Bar::mix(unsigned index) const
    {
        unsigned volume = card_[index].get_volume();
        while(volume != 0){
            index = (index + 1)% m_size_;
            volume = card_[index].get_volume();
        }
        return index;
    }

    Cocktail& Bar::operator [] (const std::string& str)
    {
        unsigned index = hasher_(str) % m_size_;
        for (unsigned i = 0; i < (*this).m_size_; i++) {
            if (card_[index].get_name() == str && card_[index].get_volume() != 0) {
                return card_[index];
            }
            index = mix(index);
        }
        return card_[index];
    }

    const Cocktail& Bar::operator [] (const std::string& str) const
    {
        unsigned index = hasher_(str) % m_size_;
        for (unsigned i = 0; i < (*this).m_size_; i++) {
            if ((card_[index].get_name() == str) && card_[index].get_volume() != 0)
                return card_[index];
            index = mix(index);
        }
        return card_[index];
    }

    Bar& Bar::swap_bar(Bar &st){
        std::swap(m_size_, st.m_size_);
        std::swap(size_, st.size_);
        std::swap(card_, st.card_);
        std::swap(volume_degree, st.volume_degree);
        return *this;
    }

    Bar &Bar::operator=(Bar &&st) noexcept
            {
        swap_bar(st);
        return *this;
    }

    Bar &Bar::operator=(const Bar &st)
    {
        Bar to_copy(st);
        swap_bar(to_copy);
        return *this;
    }

    Bar& Bar:: operator +=(Cocktail second)
    {
        if (size_ == m_size_)
            throw std::runtime_error("Tab overflow!");
        const std::string &to_add = second.get_name();
        if (((*this)[to_add]).get_volume() != 0)
            throw std::runtime_error("Cocktail already exist!");
        unsigned index = hasher_(to_add) % m_size_;
        unsigned volume = card_[index].get_volume();
        if (volume != 0)
            index = mix(index);
        card_[index] = std::move(second);
        size_ += 1;
        double degree = card_[index].get_degree();
        define_degree(degree) += card_[index].get_volume();
        return *this;
    }

    Bar:: Bar(unsigned m_size, unsigned size, Cocktail* mas): m_size_(m_size), size_{0}, card_ (new Cocktail[m_size])
    {
        try {
            m_size_ = m_size;
            volume_degree = new unsigned[4]{0,0,0,0};
            for (unsigned i = 0; i < size; i++) {
                if (mas[i].get_volume() != 0)
                *this += std::move(mas[i]);
            }
        }
        catch(const std::exception &msg) {
            delete [] volume_degree;
        }
    }

    unsigned Bar::calculate_volume(double degree)
    {
        return define_degree(degree);
    }

    std::ostream & operator <<(std::ostream &out, const Bar  &a)
    {
        if (a.empty() == Bar::Statement::EMPTY)
            out << "Bar is empty!" << std::endl;
        for (unsigned i = 0; i < a.m_size_; i++) {
            if (a.card_[i].get_volume() != 0) out << a.card_[i];
        }
        return out;
    }
    unsigned& Bar::define_degree(double degree){
        if (degree <= 25)
            return volume_degree[0];
        else if (degree <= 50)
            return volume_degree[1];
        else if (degree <= 75)
            return volume_degree[2];
        else return volume_degree[3];
    }
    Bar Bar::input()
    {
        std::cout << "Enter the max size-->";
        Bar a(get_num(std::cin,0));
        std::cin >> a;
        *this = std::move(a);

        return *this;
    }

    std::istream & operator >>(std::istream &in, Bar &a)
    {
        unsigned size = get_num(std::cin, 0, int(a.m_size_));
            for (unsigned i = 0; i < size; i++){
                Cocktail to_add(0);
                in >> to_add;
                a += std::move(to_add);
            }
        return in;
    }

    Cocktail Bar:: find_degree(double start, double finish){
        for (unsigned i = 0; i < m_size_; i++){
            if ((card_[i].get_degree() >= start) && card_[i].get_degree() <= finish && card_[i].get_volume() == pour_volume_)
                return card_[i];
        }
        Cocktail res("Sum", 0, 0);
        size_t flag = 1;

        for (unsigned i = 0; i < m_size_; i++){
            if (res.get_volume() == pour_volume_) return res;
            Cocktail& to_pour = card_[i];
            if ((to_pour.get_degree() >= start) && to_pour.get_degree() <= finish && to_pour.get_volume() != 0) {
                if (flag) {
                res.set_degree(card_[i].get_degree());
                flag = 0;
            }

                if (to_pour.get_volume() <= pour_volume_ - res.get_volume())
                    res.pour(to_pour, to_pour.get_volume());
                else
                    res.pour(to_pour, pour_volume_ - res.get_volume());
            }
        }
        if (res.get_volume() != pour_volume_)
            throw std::runtime_error("Cocktail isn't exist!");
        return res;
    }
}
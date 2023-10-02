#ifndef UNTITLED3_LAB2_H
#define UNTITLED3_LAB2_H
#include <cstring>
#include <iostream>
#include <limits>

namespace Lab2 {

    /**
     * @brief Класс, представляющий коктейль.
     */
    class Cocktail {
    private:
        std::string name_;  /**< Название коктейля. */
        unsigned volume_;   /**< Объем коктейля в миллилитрах. */
        double degree_;     /**< Крепость коктейля в процентах. */

        friend std::ostream &operator<<(std::ostream &, const Cocktail &);

        friend std::istream &operator>>(std::istream &, Cocktail &);

    public:
        /**
         * @brief Конструктор по умолчанию.
         */
        explicit Cocktail() : name_{"water"}, volume_{0}, degree_{0} {}

        /**
         * @brief Конструктор с параметрами.
         * @param name Название коктейля.
         * @param volume Объем коктейля.
         * @param degree Крепость коктейля.
         */
        explicit Cocktail(std::string name, unsigned volume, double degree);

        /**
         * @brief Конструктор с указанием только объема.
         * @param volume Объем коктейля.
         */
        explicit Cocktail(unsigned volume) : name_{"water"}, volume_{volume}, degree_{0} {}

        /**
         * @brief Конструктор перемещения.
         * @param st Коктейль для перемещения.
         */
        Cocktail(Cocktail &&st) noexcept = default;

        /**
         * @brief Конструктор копирования.
         * @param st Коктейль для копирования.
         */
        Cocktail(const Cocktail &st) = default;

        /**
         * @brief Геттер для получения названия коктейля.
         * @return Название коктейля.
         */
        [[nodiscard]] const std::string &get_name() const { return name_; }

        /**
         * @brief Геттер для получения объема коктейля.
         * @return Объем коктейля в миллилитрах.
         */
        [[nodiscard]] unsigned get_volume() const { return volume_; }

        /**
         * @brief Геттер для получения крепости коктейля.
         * @return Крепость коктейля в процентах.
         */
        [[nodiscard]] double get_degree() const { return degree_; }

        /**
         * @brief Сеттер для установки названия коктейля.
         * @param name Новое название коктейля.
         * @return Ссылка на текущий объект.
         */
        Cocktail &set_name(const std::string &name);

        /**
         * @brief Сеттер для установки объема коктейля.
         * @param volume Новый объем коктейля в миллилитрах.
         * @return Ссылка на текущий объект.
         */
        Cocktail &set_volume(unsigned volume);

        /**
         * @brief Сеттер для установки крепости коктейля.
         * @param degree Новая крепость коктейля в процентах.
         * @return Ссылка на текущий объект.
         */
        Cocktail &set_degree(double degree);

        /**
         * @brief Оператор прибавления коктейля к текущему.
         * @param second Второй коктейль для сложения.
         * @return Ссылка на текущий объект.
         */
        Cocktail &operator+(const Cocktail &second);

        /**
         * @brief Оператор присваивания для коктейля.
         * @param second Коктейль, значение которого будет скопировано.
         * @return Ссылка на текущий объект.
         */
        Cocktail &operator=(const Cocktail &second);

        /**
         * @brief Оператор умножения коктейля на число.
         * @param number Число, на которое нужно умножить объем коктейля.
         * @return Ссылка на текущий объект.
         */
        Cocktail &operator*(int number);

        /**
         * @brief Оператор переливания 100мл (или всего, если объем меньше) одного коктейля в другой.
         * @param second Второй коктейль для переливания.
         * @return Ссылка на текущий объект.
         */
        Cocktail& operator>(Cocktail &second);

        /**
         * @brief Переливание заданного объема из другого коктейля.
         * @param second Второй коктейль для переливания.
         * @param volume Значение объема для переливания.
         * @return Обновленный объект коктейля.
         */

        Cocktail& pour(Cocktail &second, unsigned volume);
    };
}

#endif

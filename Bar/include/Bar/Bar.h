#ifndef OOP_LAB2_LAB2B_H
#define OOP_LAB2_LAB2B_H

#include "Cocktail/Cocktail.h"
#include <vector>

namespace Lab2 {
    class Bar {
    private:
        unsigned m_size_ = 0; /**< Максимальный размер бара. */
        unsigned size_ = 0; /**< Текущий размер бара. */
        Cocktail *card_ = nullptr; /**< Массив коктейлей в баре. */
        unsigned *volume_degree = nullptr; /**< Массив для хранения объема и крепости коктейлей. */
        const unsigned pour_volume_{500}; /**< Объем для наливки коктейлей. */
        std::hash<std::string> hasher_{}; /**< Хеш-функция для строк. */

        /**
         * @brief Внутренняя функция для перемешивания коктейлей.
        * @param seed Начальное значение для генерации случайных чисел.
         * @return Новое значение для перемешанного коктейля.
         */
        [[nodiscard]] unsigned mix(unsigned seed) const;

        friend std::ostream &operator<<(std::ostream &, const Bar &);

        friend std::istream &operator>>(std::istream &, Bar &);

    public:
        enum class Statement {
            EMPTY,      /**< Бар пуст. */
            FULL,       /**< Бар полностью заполнен. */
            SEMI_FULL   /**< Бар частично заполнен. */
        };

        /**
        * @brief Конструктор по умолчанию.
        */
        Bar() = default;

        /**
         * @brief Конструктор с указанием максимального размера бара.
         * @param m_size Максимальный размер бара.
         */
        explicit Bar(unsigned m_size);

        /**
        * @brief Конструктор с указанием максимального размера бара, текущего размера и массива коктейлей.
        * @param m_size Максимальный размер бара.
        * @param size Текущий размер бара.
        * @param mas Массив коктейлей.
        */
        explicit Bar(unsigned m_size, unsigned size, Cocktail *mas);

        /**
         * @brief Конструктор перемещения.
         * @param st Бар для перемещения.
         */
        Bar(Bar &&st) noexcept;

        /**
         * @brief Конструктор копирования.
         * @param st Бар для копирования.
         */
        Bar(const Bar &st);

        /**
         * @brief Оператор добавления коктейля в бар.
         * @param second Коктейль для добавления.
         * @return Обновленный объект бара.
         */
        Bar &operator+=(Cocktail second);

        /**
         * @brief Оператор доступа к коктейлю по названию (константная версия).
         * @param str Название коктейля.
         * @return Константная ссылка на коктейль.
         */
        const Cocktail &operator[](const std::string &str) const;

        /**
         * @brief Оператор доступа к коктейлю по названию.
         * @param str Название коктейля.
         * @return Ссылка на коктейль.
         */
        Cocktail &operator[](const std::string &str);

        /**
         * @brief Оператор присваивания с перемещением.
         * @param st Бар для перемещения.
         * @return Обновленный объект бара.
         */
        Bar &operator=(Bar &&st) noexcept;

        /**
         * @brief Оператор присваивания копированием.
         * @param st Бар для копирования.
         * @return Обновленный объект бара.
         */
        Bar &operator=(const Bar &st);

        /**
        * @brief Ввод коктейлей в бар.
        * @return Обновленный объект бара.
        */
        Bar input();

        /**
         * @brief Проверка состояния бара.
         * @return Состояние бара (пустой, полный или частично заполнен).
         */
        [[nodiscard]] Statement empty() const;

        /**
         * @brief Удаление коктейля из бара по названию.
         * @param str Название коктейля для удаления.
         */
        void remove(const std::string &str);

        /**
         * @brief Замена названия коктейля в баре.
         * @param old_name Старое название коктейля.
         * @param new_name Новое название коктейля.
         * @return Обновленный объект бара.
         */
        Bar &change_name(const std::string &old_name, const std::string &new_name);

        /**
         * @brief Подсчёт общего объёма коктейлей по квартилям в зависимости от процента
                    алкоголя (от 0% до 25%, от 25% до 50%, от 50% до 75% и от 75% до 100%).
         * @param degree процент алкоголя коктейля(из диапазона одного из квартилям для расчета объема.
         * @return Объем коктейлей с крепостью из указанного квартилям.
         */
        unsigned calculate_volume(double degree);

        /**
         * @brief Определение объема коктейля по заданному процента алкоголя.
         * @param degree Крепость коктейля из нужного квартиля.
         * @return Ссылка на элемент массива объемов .
         */
        unsigned &define_degree(double degree);

        /**
         * @brief Обмен содержимым двух баров.
         * @param st Бар для обмена.
         * @return Обновленный объект бара.
         */
        Bar &swap_bar(Bar &st);

        /**
         * @brief Деструктор для освобождения ресурсов.
         */
        ~Bar();

        /**
         * @brief Поиск 500мл коктейля с процентом алкоголя, находящимся в заданных пределах
                    (если подходящего коктейля в данный момент нет, его необходимо смешать);.
         * @param start Начальная крепость для поиска.
         * @param finish Конечная крепость для поиска.
         * @return 500мл коктейля с крепостью в указанном диапазоне.
         */
        Cocktail find_degree(double start, double finish);
    };
}
#endif

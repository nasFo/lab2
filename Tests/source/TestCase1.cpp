#include <gtest/gtest.h>

#include <Cocktail/Cocktail.h>
#include <Bar/Bar.h>

using namespace Lab2;

// Test the constructor with parameters
TEST(CocktailTest, ConstructorWithParameters) {
    Cocktail cocktail("Margarita", 200, 10.5);
    EXPECT_EQ(cocktail.get_name(), "Margarita");
    EXPECT_EQ(cocktail.get_volume(), 200);
    EXPECT_EQ(cocktail.get_degree(), 10.5);
    Bar bar(3);
    bar += cocktail;
    const Bar& for_cock = bar;
    const Cocktail& cock = for_cock["Margarita"];
    const Cocktail& kak_poxuy = cock;
    EXPECT_EQ(cocktail.get_volume(), 200);
}

// Test the default constructor
TEST(CocktailTest, DefaultConstructor) {
    Cocktail cocktail;
    EXPECT_EQ(cocktail.get_name(), "water");
    EXPECT_EQ(cocktail.get_volume(), 0);
    EXPECT_EQ(cocktail.get_degree(), 0.0);
}

// Test setters
TEST(CocktailTest, Setters) {
    Lab2::Cocktail cocktail;
    cocktail.set_name("Cosmopolitan").set_volume(150).set_degree(15.0);
    EXPECT_EQ(cocktail.get_name(), "Cosmopolitan");
    EXPECT_EQ(cocktail.get_volume(), 150);
    EXPECT_EQ(cocktail.get_degree(), 15.0);
}

// Test operator+
TEST(CocktailTest, OperatorPlus) {
    Lab2::Cocktail cocktail1("Mojito", 250, 12.0);
    Lab2::Cocktail cocktail2("Daiquiri", 200, 11.0);

    cocktail1 + cocktail2;
    EXPECT_EQ(cocktail1.get_name(), "Mojito+Daiquiri");
    EXPECT_EQ(cocktail1.get_volume(), 450);
    EXPECT_NEAR(cocktail1.get_degree(), (11.0 + 12.0)/2, 0.5);
}

// Test operator>
TEST(CocktailTest, OperatorGreater) {
    Lab2::Cocktail cocktail1("Martini", 180, 14.0);
    Lab2::Cocktail cocktail2("Negroni", 200, 12.5);

    cocktail1 > cocktail2;

    EXPECT_EQ(cocktail1.get_name(), "Martini");
    EXPECT_EQ(cocktail1.get_volume(), 280);
    EXPECT_EQ(cocktail1.get_degree(), 14.0);

    EXPECT_EQ(cocktail2.get_name(), "Negroni");
    EXPECT_EQ(cocktail2.get_volume(), 100);
    EXPECT_EQ(cocktail2.get_degree(), 12.5);

}

// Test operator*
TEST(CocktailTest, OperatorMultiply) {
    Lab2::Cocktail cocktail("Tequila Sunrise", 300, 9.5);
    int multiplier = 3;

    Lab2::Cocktail result = cocktail * multiplier;
    EXPECT_EQ(result.get_name(), "Tequila Sunrise");
    EXPECT_EQ(result.get_volume(), 900);
    EXPECT_EQ(result.get_degree(), 9.5);
}

// Test pour method
TEST(CocktailTest, Pour) {
    Lab2::Cocktail cocktail1("Pina Colada", 250, 12.0);
    Lab2::Cocktail cocktail2("Blue Lagoon", 200, 10.0);

    cocktail1.pour(cocktail2, 50);

    EXPECT_EQ(cocktail1.get_volume(), 300);
    EXPECT_EQ(cocktail2.get_volume(), 150);
    EXPECT_NEAR(cocktail1.get_degree(), (10 + 12) / 2, 0.5);
}


TEST(CocktailTest, OutputOperator) {
    Cocktail cock(100);
    testing::internal::CaptureStdout();
    std::cout << cock;
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "water 100 0\n");
}

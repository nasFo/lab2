#include <gtest/gtest.h>
#include "Bar/Bar.h"  // Include the Bar class header
#include "Cocktail/Cocktail.h"   // Include the Cocktail class header

using namespace Lab2;

// Test the Bar constructor with a size parameter
TEST(BarTest, ConstructorWithSize) {
    Bar bar(5);
    EXPECT_EQ(bar.empty(), Lab2::Bar::Statement::EMPTY);
   // EXPECT_EQ((bar.find_degree(10.0, 11.0)).get_volume(), 0);
}

// Test the Bar constructor with size, initial size, and an array of Cocktails
TEST(BarTest, ConstructorWithSizeAndCocktails) {
    Cocktail cocktails[3];
    cocktails[0] = Cocktail("Cocktail1", 500, 8.0);
    cocktails[1] = Cocktail("Cocktail2", 250, 12.0);
    cocktails[2] = Cocktail("Cocktail3", 350, 10.0);

    Bar bar(3, 3, cocktails);
    EXPECT_EQ(bar.empty(), Lab2::Bar::Statement::FULL);
    Bar bar2(3);
    bar2 = bar;
    EXPECT_EQ(bar2.empty(), Lab2::Bar::Statement::FULL);
    EXPECT_EQ(bar2.find_degree(0, 9).get_name(), "Cocktail1");
    EXPECT_EQ(bar2.find_degree(10, 12).get_degree(), 11);
}

// Test the += operator to add Cocktails to the Bar
TEST(BarTest, OperatorPlusEqual) {
    Bar bar(3);
    Cocktail cocktail("TestCocktail", 200, 10.5);
    bar += cocktail;
    EXPECT_EQ(bar.empty(), Lab2::Bar::Statement::SEMI_FULL);
    EXPECT_EQ(bar.calculate_volume(10.5), 200);
}

// Test the [] operator to access Cocktails by name
TEST(BarTest, OperatorBrackets) {
    Bar bar(3);
    Cocktail cocktail("Cocktail1", 150, 8.0);
    bar += cocktail;
    EXPECT_EQ((bar["Cocktail1"]).get_name(), "Cocktail1");
    EXPECT_EQ(bar["NonExistentCocktail"].get_name(), "water");
    const Bar& for_cock = bar;
    const Cocktail& cock = for_cock["Cocktail1"];
    EXPECT_EQ(cock.get_name(), "Cocktail1");
}

// Test the remove method to remove a Cocktail from the Bar
TEST(BarTest, RemoveCocktail) {
    Bar bar(3);
    Cocktail cocktail("Cocktail1", 150, 8.0);
    bar += cocktail;
    bar.remove("Cocktail1");
    EXPECT_EQ(bar.empty(), Lab2::Bar::Statement::EMPTY);
}

// Test the change_name method to change the name of a Cocktail
TEST(BarTest, ChangeCocktailName) {
    Bar bar(3);
    Cocktail cocktail("Cocktail1", 150, 8.0);
    bar += cocktail;
    bar.change_name("Cocktail1", "NewName");
    EXPECT_EQ(bar["NewName"].get_degree(), 8);
    Bar barrister(bar);
    EXPECT_EQ(barrister.empty(), Lab2::Bar::Statement::SEMI_FULL);
    EXPECT_EQ(barrister["NewName"].get_degree(), 8);
}

TEST(BarTest, OutputOperator) {
    Bar bar(1);
    testing::internal::CaptureStdout();
    std::cout << bar;
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Bar is empty!\n");
    Cocktail a("vodka", 100, 40);
    bar += a;
    Bar bar_new(std::move(bar));
    EXPECT_EQ(bar_new.empty(), Lab2::Bar::Statement::FULL);
}

TEST(BarTest, Calculate_degree) {
    Cocktail cocktails[3];
    cocktails[0] = Cocktail("Cocktail1", 500, 70.0);
    cocktails[1] = Cocktail("Cocktail2", 250, 30.0);
    cocktails[2] = Cocktail("Cocktail3", 350, 90.0);

    Bar bar(3, 3, cocktails);
    EXPECT_EQ(bar.empty(), Lab2::Bar::Statement::FULL);
    Bar bar2(3);
    bar2 = std::move(bar);
    EXPECT_EQ(bar2.calculate_volume(70), 500);
    EXPECT_EQ(bar2.calculate_volume(26), 250);
    EXPECT_EQ(bar2.calculate_volume(92), 350);
}

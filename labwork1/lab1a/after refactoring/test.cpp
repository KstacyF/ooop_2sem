#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "polynom.h"
TEST_CASE("Testing Polinom 1")
{
    SUBCASE("Test addition")
    {
        Polynom p1("1x^2+3x^1+5x^0");
        Polynom p2("1x^4+4x^2+3x^0");
        Polynom p3("1x^4+5x^2+3x^1+8x^0");

        Polynom p4 = p1 + p2;

        REQUIRE(p4 == p3);
    }

    SUBCASE("Test multiplication")
    {
        Polynom p1("1x^1+1x^0");
        Polynom p2("1x^2+2x^1+1x^0");

        Polynom p3 = p1 * p1;

        REQUIRE(p3 == p2);
    }

    SUBCASE("Test division")
    {
        Polynom p1("1x^4+1x^3-3x^1+7x^0");
        Polynom p2("1x^2-4x^0");
        Polynom q("1x^2+1x^1+4x^0");
        Polynom r("1x^1+23x^0");

        std::pair<Polynom, Polynom> d = p1 / p2;
        Polynom quo = d.first;
        Polynom rem = d.second;

        REQUIRE((quo == q));
        REQUIRE((rem == r));
    }
}
/// @file pa13.cpp
/// @author Sujin Lee
/// @date 2022-02-24
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief Catch2 Unit tests for the dynamic Container

#define CATCH_CONFIG_MAIN
#if defined __linux__
#include <catch.hpp>
#elif defined __MACH__
#include </opt/local/include/catch2/catch.hpp>
#else
#include "catch.hpp"
#endif

#include <algorithm>
#include <sstream>
#include <iostream>

#include "Container.h"

TEST_CASE("Container(size_type)") {
    Container box1;

    CHECK(box1.size() == 0);
    CHECK(box1.empty() == true);

    Container box2(42);

    CHECK(box2.size() == 0);
    CHECK(box2.empty() == true);
}

TEST_CASE("Container(const Container&)") {
    const Container box1 { 65, 66, 67, 68, 69, 70 };

    CHECK(box1.size() == 6);

    Container box2(box1);

    CHECK(box1.begin() != box2.begin());
    CHECK(box1.size() == box2.size());
    CHECK(std::equal(box1.begin(), box1.end(), box2.begin(), box2.end()) == true);
}

TEST_CASE("Container(initializer_list)") {
    const Container box1 { 65, 66, 67, 68, 69, 70 };

    CHECK(box1.size() == 6);

    for (int i = 0; i < 6; ++i) {
        CHECK(*(box1.begin() + i) == *box1.begin() + i);
    }
}

TEST_CASE("~Container()") {}

TEST_CASE("empty()") {
    Container box1;

    CHECK(box1.empty() == true);

    box1.push_back(42);
    CHECK(box1.empty() == false);

    box1.clear();
    CHECK(box1.empty() == true);
}

TEST_CASE("size()") {
    Container box1(6);

    CHECK(box1.size() == 0);

    for (int i = 1; i <= 6; ++i) {
        box1.push_back(i);
        CHECK(static_cast<int>(box1.size()) == i);
    }

    box1.clear();
    CHECK(box1.size() == 0);
}

TEST_CASE("begin()") {}
TEST_CASE("begin() const") {}
TEST_CASE("end()") {}
TEST_CASE("end() const") {}

TEST_CASE("push_back()") {
    const std::initializer_list<Container::value_type> init = {
        65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81
    };

    Container box1;
    const Container::pointer original_array = box1.begin();

    CHECK(box1.size() == 0);

    for (Container::value_type value : init) {
        box1.push_back(value);
    }

    CHECK(box1.size() == init.size());
    CHECK(box1.begin() != original_array);

    CHECK(std::equal(box1.begin(), box1.end(), init.begin(), init.end()) == true);
}

TEST_CASE("erase()") {
    Container box1 { 65, 66, 67, 68 };

    // delete last element
    box1.erase(box1.end() - 1);
    CHECK(box1.size() == 3);
    CHECK(box1.find(68) == box1.end());

    // delete middle element
    box1.erase(box1.begin() + box1.size() / 2);
    CHECK(box1.size() == 2);
    CHECK(box1.find(66) == box1.end());

    // delete front element
    box1.erase(box1.begin());
    CHECK(box1.size() == 1);
    CHECK(box1.find(65) == box1.end());

    CHECK(*box1.begin() == 67);
    box1.erase(box1.begin());
    CHECK(box1.empty() == true);
    CHECK(box1.size() == 0);
}

TEST_CASE("clear()") {
    Container box1 { 65, 66, 67, 68 };
    box1.clear();
    CHECK(box1.empty() == true);
}

TEST_CASE("swap(Container&)") {
    Container box1 { 65, 66, 67, 68 };
    Container box2;

    box1.swap(box2);

    CHECK(box1.empty() == true);
    REQUIRE(box2.size() == 4);

    for (Container::value_type i = 0; i < 4; ++i) {
        CHECK(*(box2.begin() + i) == 65 + i);
    }
}

TEST_CASE("find(const value_type&, pointer)") {
    Container box1 { 42, 65, 66, 67, 42, 68, 69, 42 };

    CHECK(box1.find(42) == box1.begin());
    // CHECK(box1.find(42, box1.begin() + 1) == box1.begin() + 4);
    // CHECK(box1.find(42, box1.begin() + 5) == box1.begin() + 7);
    CHECK(box1.find(73) == box1.end());
}

TEST_CASE("equal(const Container&, const Container&)") {
    Container box1 { 65, 66, 67, 68 };
    Container box2 { 65, 66, 67, 68 };

    CHECK(equal(box1, box2) == true);

    *(box2.begin() + 2) = 42;

    CHECK(equal(box1, box2) == false);
}

TEST_CASE("write(std::ostream&, const Container&)") {
    Container box1;
    Container box2 { 65, 66, 67, 68, 69 };
    std::ostringstream output;

    write(output, box1);

    CHECK(output.str() == "{}");

    output.str("");

    write(output, box2);

    CHECK(output.str() == "{65,66,67,68,69}");
}

TEST_CASE("operator=") {
    Container box1;
    Container box2 { 65, 66, 67, 68, 69 };

    box1 = box2;

    CHECK(equal(box1, box2) == true);

    *(box2.begin() + 2) = 42;

    CHECK(equal(box1, box2) == false);

}

TEST_CASE("operator+=") {
    Container box1 { 1, 2, 3, 4, 5 };
    Container box2 { 65, 66, 67, 68, 69 };
    Container box3 { 1, 2, 3, 4, 5, 65, 66, 67, 68, 69 };

    box1 += box2;

    CHECK( equal(box1, box3) == true );

}

TEST_CASE("operator==") {
    Container box1 { 1, 2, 3, 4, 5 };
    Container box2 { 1, 2, 3, 4, 5 };

    CHECK((box1 == box2) == true);

    *(box2.begin() + 2) = 42;

    CHECK((box1 == box2) == false);

}

TEST_CASE("operator!=") {
    Container box1 { 1, 2, 3, 4, 5 };
    Container box2 { 1, 2, 3, 4, 5 };

    CHECK((box1 != box2) == false);

    *(box2.begin() + 2) = 42;

    CHECK((box1 != box2) == true);
}

TEST_CASE("operator+") {
    Container box1 { 1, 2, 3 };
    Container box2 { 4, 5 };
    Container box3;

    box3 = box1 + box2;

    std::ostringstream output;
    write(output, box3);
    CHECK(output.str() == "{1,2,3,4,5}");
}

TEST_CASE("operator<<") {
    Container box1 { 1, 2, 3 };
    std::ostringstream cout;
    cout << box1;

    CHECK( cout.str() == "{1,2,3}" );

}

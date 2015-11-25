#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>
#include "../minimal-parser/minimal-parser.h"

TEST_GROUP(FindGPRMC) {
};

TEST(FindGPRMC, Find1) {
    char test[7];
    STATUS status = parse(test);
    CHECK(true);
}

int main(int argc, char** argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}


#include <fstream>      // std::ifstream
#include <iostream>     // std::cout

#include "../minimal-parser/minimal-parser.h"

#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>

using namespace std;

void readFile(const char* filename, char** buffer);

const char* testDataAlignedFileName = "test-data-aligned.txt";
char* testDataAlignedBuffer;

const char* testDataNotAlignedFileName = "test-data-not-aligned.txt";
char* testDataNotAlignedBuffer;

TEST_GROUP(FindGPRMC) {
    void setup() {
        readFile(testDataAlignedFileName, &testDataAlignedBuffer);
        cout << "testDataAlignedBuffer:" << endl << testDataAlignedBuffer << endl;
        readFile(testDataNotAlignedFileName, &testDataNotAlignedBuffer);
        cout << "testDataNotAlignedBuffer:" << endl << testDataNotAlignedBuffer << endl;
    }

    void teardown() {
        delete[] testDataAlignedBuffer;
        delete[] testDataNotAlignedBuffer;
    }
};

void readFile(const char* filename, char** buffer) {
    ifstream inputFile(filename, ifstream::binary);
    if (!inputFile) {
        FAIL("Unable to open input file.");
    }
    inputFile.seekg(0, inputFile.end);
    long length = inputFile.tellg();
    inputFile.seekg(0, inputFile.beg);
    
    *buffer = new char[length];

    inputFile.read(*buffer, length);

    if(!inputFile) {
        FAIL("Failed to read file.");
    }

    inputFile.close();
}

TEST(FindGPRMC, Find1) {
    char test[7];
    STATUS status = parse(test);
    CHECK(true);
}

int main(int argc, char** argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}


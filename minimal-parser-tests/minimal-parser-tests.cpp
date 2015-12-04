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
        readFile(testDataNotAlignedFileName, &testDataNotAlignedBuffer);
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
    long bufferSize = 138;
    char testStr[bufferSize];
    memcpy(testStr, testDataAlignedBuffer, bufferSize);
    
    min_parser_data* result;

    long internalBufferSize = getMinInternalBufferSize();
    char input[internalBufferSize];
    STATUS status = 0;
    for (int i=0;i < bufferSize;i++) {
        input[i % internalBufferSize] = testStr[i];
        if (i % internalBufferSize == internalBufferSize - 1) {
            status = minParse(input);
            if (status == 1) {
                getMinData(&result);
                CHECK(result->latCoord == 3729.20844);
                CHECK(result->latHem == 'N');
                CHECK(result->longCoord == 12213.94165);
                CHECK(result->longHem == 'W');
                break;
            }
        }
    }

    CHECK(status == 1);
}

int main(int argc, char** argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}


#include "parser-impl.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// STATUS returned to the user of the function
static STATUS status = 0;
static char* currentBuffer;
static char previousBuffer[MIN_PARSER_INTERNAL_BUFFER_SIZE];
static char header[] = {'$', 'G', 'P', 'R', 'M', 'C', ','};
static unsigned char indexHeader = 0;
enum State {SEARCHING_HEADER, SKIPPING_TIME, PARSING_STATUS, PARSING_LAT_COORD, PARSING_LAT_HEM, PARSING_LONG_COORD, PARSING_LONG_HEM, DONE};

static State state = SEARCHING_HEADER;

void searchHeader(char c);

void skipTime(char c, char i);

void parseStatus(char c, char i);

void parseCoord(char c, char i, double* result, State nextState);

void parseHem(char c, char i, char* result, State nextState);

STATUS _minParse(char* inputBuffer, min_parser_data* result) {
    currentBuffer = inputBuffer;
    for (char i=0;i < MIN_PARSER_INTERNAL_BUFFER_SIZE;i++) {
        char c = inputBuffer[i];

        switch(state) {
            case SEARCHING_HEADER: searchHeader(c); break;
            case SKIPPING_TIME: skipTime(c, i); break;
            case PARSING_STATUS: parseStatus(c, i); break;
            case PARSING_LAT_COORD: parseCoord(c, i, &(result->latCoord), PARSING_LAT_HEM); break;
            case PARSING_LAT_HEM: parseHem(c, i, &(result->latHem), PARSING_LONG_COORD); break;
            case PARSING_LONG_COORD: parseCoord(c, i, &(result->longCoord), PARSING_LONG_HEM); break;
            case PARSING_LONG_HEM: parseHem(c, i, &(result->longHem), DONE); break;
            case DONE: status = 1; break;
            default: state = SEARCHING_HEADER; break;
        }
    }

    memcpy(previousBuffer, currentBuffer, MIN_PARSER_INTERNAL_BUFFER_SIZE);

    return status;
}

void searchHeader(char c) {
    if (c == header[indexHeader]) {
        indexHeader++;
        if (indexHeader == sizeof header) {
            // Found header
            indexHeader = 0;
            state = SKIPPING_TIME;
            return;
        }
    } else {
        indexHeader = 0;
    }
}

void skipTime(char c, char i) {
    if (c == ',') {
        state = PARSING_STATUS;
    }
}

void parseStatus(char c, char i) {
    if (c == 'V') {
        // Interrupt parsing of coordinates and search for header again
        state = SEARCHING_HEADER;
        if (status == 0) {
            // If never been able to parse before, switch to status: 
            // "parsed at least once, but no gps data available (gps not 
            // aligned)"
            status = 2;
        } else if (status == 1){
            // If parsed valid gps data before, switch to state:
            // "successfuly parsed valid gps data before, but last parsed 
            // data had no valid gps data (gps was aligned before at some 
            // point, but was not aligned the last time data was parsed, so 
            // data is stale.)"
            status = 3;
        }
    } else if (c == ',') {
        // Go to next state so parsing process keeps going
        state = PARSING_LAT_COORD;
    }
}

void parseCoord(char c, char i, double* result, State nextState) {
    if (c == ',') {
        char buffer[MIN_PARSER_INTERNAL_BUFFER_SIZE];
        char bufferIndex = MIN_PARSER_INTERNAL_BUFFER_SIZE - 1;
        char* processingBuffer = currentBuffer;
        for (char j=bufferIndex;j >= 0;j--) {
            i--;
            if (i < 0) {
                i = MIN_PARSER_INTERNAL_BUFFER_SIZE - 1;
                processingBuffer = previousBuffer;
            }
            char processingChar = processingBuffer[i];
            if (processingChar == '\0') {
                continue;
            } else if( processingChar == ',') {
                break;
            }
            
            buffer[bufferIndex--] = processingChar;
        }
        
        // Shift the parsed number to the beginning of the buffer
        for (char j=0;j < MIN_PARSER_INTERNAL_BUFFER_SIZE;j++) {
            if (++bufferIndex < MIN_PARSER_INTERNAL_BUFFER_SIZE) {
                buffer[j] = buffer[bufferIndex];
            } else {
                buffer[j] = '\0';
            }
        }

        *result = atof(buffer);
        state = nextState;
    } 
}

void parseHem(char c, char i, char* result, State nextState) {
    if (c == ',') {
        if (i == 0) {
            *result = previousBuffer[MIN_PARSER_INTERNAL_BUFFER_SIZE - 1];
        } else {
            *result = currentBuffer[i-1];
        }

        state = nextState;
    } 
}


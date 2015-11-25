#ifndef MIN_PARSER_H
#define MIN_PARSER_H

#define STATUS unsigned char

typedef struct {
    float latCoord;
    char latHem;
    float longCoord;
    char longHem;
} min_parser_data;

STATUS parse(char* data);

STATUS getData(min_parser_data* data);

#endif

#ifndef MIN_PARSER_H
#define MIN_PARSER_H

#define STATUS unsigned char

struct min_parser_data {
    float latCoord;
    char latHem;
    float longCoord;
    char longHem;
};

STATUS parse(char* data);

STATUS getData(struct min_parser_data* data);

#endif

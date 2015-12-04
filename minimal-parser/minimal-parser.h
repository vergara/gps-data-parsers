#ifndef MIN_PARSER_H
#define MIN_PARSER_H

#include "../status/status.h"

typedef struct {
    double latCoord;
    char latHem;
    double longCoord;
    char longHem;
} min_parser_data;

STATUS minParse(char* data);

STATUS getMinData(min_parser_data** data);

long getMinInternalBufferSize();

#endif

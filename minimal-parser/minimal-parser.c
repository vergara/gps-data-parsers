#include "minimal-parser.h"
#include "parser-impl/parser-impl.h"
#include <string.h>

static min_parser_data _data;
static STATUS _status; 

STATUS minParse(char* data) {
    return _minParse(data, &_data);
}

STATUS getMinData(min_parser_data** data) {
    *data = &_data;
    return _status;
}

long getMinInternalBufferSize() {
    return MIN_PARSER_INTERNAL_BUFFER_SIZE;
}


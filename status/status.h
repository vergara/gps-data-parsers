#ifndef STATUS_H
#define STATUS_H

/**
 * 0: Unable to parse data until now.
 * 1: parsed, valid data.
 * 2: parsed, no data, unable to parse valid data until now.
 * 3: parsed, no data, but data is available from a previous call to parse().
 * Call to getData() returns stale data.
 */
#define STATUS unsigned char

#endif

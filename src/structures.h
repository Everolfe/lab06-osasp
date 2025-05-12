#ifndef INC_6LABA_STRUCTURES_H
#define INC_6LABA_STRUCTURES_H

#include <stdint.h>

typedef struct {
    double time_mark;
    uint64_t recno;
} index_record_t;

typedef struct {
    uint64_t records;
    index_record_t * idx;
} index_hdr_t;

#endif //INC_6LABA_STRUCTURES_H
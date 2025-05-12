#define _POSIX_C_SOURCE 200112L

#include "structures.h"
#include <stdio.h>
#include <stdlib.h>

void open_file_or_exit(const char *file_name, FILE **file, char *mode);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong number of parameters.\n");
        exit(EXIT_FAILURE);
    }

    FILE *file;
    open_file_or_exit(argv[1], &file, "rb");

    index_hdr_t *data = (index_hdr_t *) malloc(sizeof(index_hdr_t));
    if (!fread(&data->records, sizeof(uint64_t), 1, file)) {
        printf("Failed to read records.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    data->idx = (index_record_t *) malloc(data->records * sizeof(index_record_t));
    if (!fread(data->idx, sizeof(index_record_t), data->records, file)) {
        printf("Failed to read idx.\n");
        fclose(file);
        free(data->idx);
        free(data);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < (int) data->records; i++)
        printf("%lf\n", data->idx[i].time_mark);

    fclose(file);

    free(data->idx);
    free(data);
    return 0;
}

void open_file_or_exit(const char *file_name, FILE **file, char *mode) {
    *file = fopen(file_name, mode);
    if (*file == NULL) {
        printf("Failed to open file.\n");
        exit(EXIT_FAILURE);
    }
}
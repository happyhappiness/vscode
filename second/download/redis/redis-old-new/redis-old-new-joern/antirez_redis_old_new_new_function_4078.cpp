int main(int argc, char **argv) {
    /* expect the first argument to be the dump file */
    if (argc <= 1) {
        printf("Usage: %s [--fix] <file.aof>\n", argv[0]);
        exit(0);
    }

    char *filename;
    int fix = 0;
    if (argc == 3) {
        if (strcmp(argv[1],"--fix") != 0) {
            printf("Invalid argument: %s\n", argv[1]);
            exit(1);
        }
        fix = 1;
        filename = argv[2];
    } else if (argc == 2) {
        filename = argv[1];
    } else {
        printf("Invalid argument");
        exit(1);
    }

    FILE *fp = fopen(filename,"r+");
    if (fp == NULL) {
        printf("Cannot open file: %s\n", filename);
        exit(1);
    }

    struct redis_stat sb;
    if (redis_fstat(fileno(fp),&sb) == -1) {
        printf("Cannot stat file: %s\n", filename);
        exit(1);
    }

    long size = sb.st_size;
    if (size == 0) {
        printf("Empty file: %s\n", filename);
        exit(1);
    }

    long pos = process(fp);
    if (pos < size) {
        if (fix) {
            if (ftruncate(fileno(fp), pos) == -1) {
                printf("Could not truncate AOF to size %ld\n", pos);
                exit(1);
            } else {
                printf("AOF succesfully truncated to %ld bytes\n", pos);
            }
        } else {
            printf("First invalid operation at offset %ld\n", pos);
        }
    } else {
        printf("AOF is valid\n");
    }

    fclose(fp);
    return 0;
}
int main(int argc, char **argv) {
    /* expect the first argument to be the dump file */
    if (argc <= 1) {
        printf("Usage: %s <file.aof>\n", argv[0]);
        exit(0);
    }

    FILE *fp = fopen(argv[1],"r");
    if (fp == NULL) {
        printf("Cannot open file: %s\n", argv[1]);
        exit(1);
    }

    struct redis_stat sb;
    if (redis_fstat(fileno(fp),&sb) == -1) {
        printf("Cannot stat file: %s\n", argv[1]);
        exit(1);
    }

    long size = sb.st_size;
    if (size == 0) {
        printf("Empty file: %s\n", argv[1]);
        exit(1);
    }

    long pos = process(fp);
    if (pos < size) {
        printf("First invalid operation at offset %ld.\n", pos);
        exit(1);
    } else {
        printf("AOF is valid.\n");
    }

    fclose(fp);

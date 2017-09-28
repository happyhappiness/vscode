    if (strlen(error) > 0) {
        printf("%s\n", error);
    }
    return pos;
}

int redis_check_aof_main(int argc, char **argv) {
    char *filename;
    int fix = 0;

    if (argc < 2) {
        printf("Usage: %s [--fix] <file.aof>\n", argv[0]);
        exit(1);

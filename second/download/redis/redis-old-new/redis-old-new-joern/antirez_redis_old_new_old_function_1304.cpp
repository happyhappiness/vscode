int redis_check_rdb(char *rdbfilename) {
    int fd;
    off_t size;
    struct stat stat;
    void *data;

    fd = open(rdbfilename, O_RDONLY);
    if (fd < 1) {
        ERROR("Cannot open file: %s\n", rdbfilename);
    }
    if (fstat(fd, &stat) == -1) {
        ERROR("Cannot stat: %s\n", rdbfilename);
    } else {
        size = stat.st_size;
    }

    if (sizeof(size_t) == sizeof(int32_t) && size >= INT_MAX) {
        ERROR("Cannot check dump files >2GB on a 32-bit platform\n");
    }

    data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        ERROR("Cannot mmap: %s\n", rdbfilename);
    }

    /* Initialize static vars */
    positions[0].data = data;
    positions[0].size = size;
    positions[0].offset = 0;
    errors.level = 0;

    /* Object types */
    sprintf(types[REDIS_STRING], "STRING");
    sprintf(types[REDIS_LIST], "LIST");
    sprintf(types[REDIS_SET], "SET");
    sprintf(types[REDIS_ZSET], "ZSET");
    sprintf(types[REDIS_HASH], "HASH");

    /* Object types only used for dumping to disk */
    sprintf(types[REDIS_EXPIRETIME], "EXPIRETIME");
    sprintf(types[REDIS_SELECTDB], "SELECTDB");
    sprintf(types[REDIS_EOF], "EOF");

    /* Double constants initialization */
    R_Zero = 0.0;
    R_PosInf = 1.0/R_Zero;
    R_NegInf = -1.0/R_Zero;
    R_Nan = R_Zero/R_Zero;

    process();

    munmap(data, size);
    close(fd);
    return 0;
}
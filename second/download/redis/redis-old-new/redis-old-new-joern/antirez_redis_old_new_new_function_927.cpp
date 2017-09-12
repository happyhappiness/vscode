int redis_check_rdb(char *rdbfilename) {
    int fd;
    off_t size;
    struct stat stat;
    void *data;

    fd = open(rdbfilename, O_RDONLY);
    if (fd < 1) {
        ERROR("Cannot open file: %s", rdbfilename);
    }
    if (fstat(fd, &stat) == -1) {
        ERROR("Cannot stat: %s", rdbfilename);
    } else {
        size = stat.st_size;
    }

    if (sizeof(size_t) == sizeof(int32_t) && size >= INT_MAX) {
        ERROR("Cannot check dump files >2GB on a 32-bit platform");
    }

    data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        ERROR("Cannot mmap: %s", rdbfilename);
    }

    /* Initialize static vars */
    positions[0].data = data;
    positions[0].size = size;
    positions[0].offset = 0;
    errors.level = 0;

    /* Object types */
    sprintf(types[RDB_TYPE_STRING], "STRING");
    sprintf(types[RDB_TYPE_LIST], "LIST");
    sprintf(types[RDB_TYPE_SET], "SET");
    sprintf(types[RDB_TYPE_ZSET], "ZSET");
    sprintf(types[RDB_TYPE_HASH], "HASH");

    /* Object types only used for dumping to disk */
    sprintf(types[RDB_OPCODE_EXPIRETIME], "EXPIRETIME");
    sprintf(types[RDB_OPCODE_SELECTDB], "SELECTDB");
    sprintf(types[RDB_OPCODE_EOF], "EOF");

    process();

    munmap(data, size);
    close(fd);
    return 0;
}
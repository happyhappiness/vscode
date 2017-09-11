
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

inline int
    shm_open(const char *, int, mode_t) {
        errno = ENOTSUP;
        return -1;
    }
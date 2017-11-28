inline int
    shm_unlink(const char *) {
        errno = ENOTSUP;
        return -1;
    }
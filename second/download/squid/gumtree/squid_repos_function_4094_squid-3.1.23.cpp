static int index_serial_LHASH_COMP(const void *arg1, const void *arg2) {
        return index_serial_cmp((const char **)arg1, (const char **)arg2);
    }
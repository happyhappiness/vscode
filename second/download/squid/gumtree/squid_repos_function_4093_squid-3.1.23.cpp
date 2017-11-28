static unsigned long index_serial_LHASH_HASH(const void *a) {
        return index_serial_hash((const char **)a);
    }
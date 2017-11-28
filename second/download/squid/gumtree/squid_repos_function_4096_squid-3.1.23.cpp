static int index_name_LHASH_COMP(const void *arg1, const void *arg2) {
        return index_name_cmp((const char **)arg1, (const char **)arg2);
    }
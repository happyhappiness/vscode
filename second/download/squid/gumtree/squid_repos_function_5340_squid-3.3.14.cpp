T *release() {
        T *ret = raw;
        raw = NULL;
        return ret;
    }
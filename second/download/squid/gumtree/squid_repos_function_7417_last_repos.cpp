T *release() {
        T *ret = raw;
        raw = nullptr;
        return ret;
    }
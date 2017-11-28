void resetWithoutLocking(T *t) {
        unlock();
        raw = t;
    }
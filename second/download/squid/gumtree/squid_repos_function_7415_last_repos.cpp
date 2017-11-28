void resetAndLock(T *t) {
        if (t != get()) {
            resetWithoutLocking(t);
            lock(t);
        }
    }
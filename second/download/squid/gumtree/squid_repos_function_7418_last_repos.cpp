void lock(T *t) {
        if (t) {
            Locker doLock;
            doLock(t);
        }
    }
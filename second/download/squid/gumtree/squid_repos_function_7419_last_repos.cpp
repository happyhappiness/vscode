void unlock() {
        if (raw) {
            UnLocker(raw);
            raw = nullptr;
        }
    }
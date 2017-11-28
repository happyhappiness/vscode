void deletePointer() {
        if (raw) {
            DeAllocator(raw);
        }
        raw = NULL;
    }
void operator() (store_client const &x) {
        if (x.memReaderHasLowerOffset(current))
            current = x.copyInto.offset;
    }
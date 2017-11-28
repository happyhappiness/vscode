void operator()(CBDataCall const &x) {
        storeAppendPrintf(where, "%s\t%s\t%d\n", x.label, x.file, x.line);
    }
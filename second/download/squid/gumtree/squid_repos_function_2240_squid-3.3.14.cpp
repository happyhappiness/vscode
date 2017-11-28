void operator()(store_client const &x) {
        x.dumpStats(where, index);
        ++index;
    }
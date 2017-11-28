void operator()(cbdata const &x) {
        CBDataDumper::operator()(x);
        storeAppendPrintf(where, "\n");
        storeAppendPrintf(where, "Action\tFile\tLine\n");
        std::for_each (x.calls.begin(), x.calls.end(), callDumper);
        storeAppendPrintf(where, "\n");
    }
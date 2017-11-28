
#if USE_CBDATA_DEBUG

struct CBDataCallDumper : public unary_function<CBDataCall, void> {
    CBDataCallDumper (StoreEntry *anEntry):where(anEntry) {}

    void operator()(CBDataCall * const &x) {
        storeAppendPrintf(where, "%s\t%s\t%d\n", x->label, x->file, x->line);
    }

    StoreEntry *where;
};

struct CBDataHistoryDumper : public CBDataDumper {
    CBDataHistoryDumper(StoreEntry *anEntry):CBDataDumper(anEntry),where(anEntry), callDumper(anEntry) {}

    void operator()(cbdata const &x) {
        CBDataDumper::operator()(x);
        storeAppendPrintf(where, "\n");
        storeAppendPrintf(where, "Action\tFile\tLine\n");
        std::for_each (x.calls.begin(), x.calls.end(), callDumper);
        storeAppendPrintf(where, "\n");
    }

    StoreEntry *where;
    CBDataCallDumper callDumper;
};

#endif
            storeAppendPrintf(sentry, "%s\t%d\t%ld\t%ld\n", pool->objectType() + 7, obj_size, (long int)pool->getMeter().inuse.level, (long int)obj_size * pool->getMeter().inuse.level);
        }
    }

#else
    storeAppendPrintf(sentry, "detailed allocation information only available when compiled with CBDATA_DEBUG\n");

#endif

    storeAppendPrintf(sentry, "\nsee also \"Memory utilization\" for detailed per type statistics\n");
}

CBDATA_CLASS_INIT(generic_cbdata);

#if CBDATA_DEBUG

struct CBDataCallDumper : public unary_function<CBDataCall, void> {
    CBDataCallDumper (StoreEntry *anEntry):where(anEntry) {}

    void operator()(CBDataCall const &x) {
        storeAppendPrintf(where, "%s\t%s\t%d\n", x.label, x.file, x.line);

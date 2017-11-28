    storeAppendPrintf(sentry, "types\tsize\tallocated\ttotal\n");

    for (int i = 1; i < cbdata_types; ++i) {
        MemAllocator *pool = cbdata_index[i].pool;

        if (pool) {
#if HASHED_CBDATA
            int obj_size = pool->objectSize();
#else
            int obj_size = pool->objectSize() - cbdata::Offset;
#endif
            storeAppendPrintf(sentry, "%s\t%d\t%ld\t%ld\n", pool->objectType() + 7, obj_size, (long int)pool->getMeter().inuse.level, (long int)obj_size * pool->getMeter().inuse.level);
        }
    }

#else
    storeAppendPrintf(sentry, "detailed allocation information only available when compiled with --enable-debug-cbdata\n");


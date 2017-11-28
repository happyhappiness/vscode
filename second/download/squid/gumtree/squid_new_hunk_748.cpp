    CacheDigestStats stats;
    assert(cd && e);
    cacheDigestStats(cd, &stats);
    storeAppendPrintf(e, "%s digest: size: %d bytes\n",
                      label ? label : "", stats.bit_count / 8
                     );
    storeAppendPrintf(e, "\t entries: count: %" PRIu64 " capacity: %" PRIu64 " util: %d%%\n",
                      cd->count,
                      cd->capacity,
                      xpercentInt(cd->count, cd->capacity)
                     );
    storeAppendPrintf(e, "\t deletion attempts: %" PRIu64 "\n",
                      cd->del_count
                     );
    storeAppendPrintf(e, "\t bits: per entry: %d on: %d capacity: %d util: %d%%\n",
                      cd->bits_per_entry,
                      stats.bit_on_count, stats.bit_count,
                      xpercentInt(stats.bit_on_count, stats.bit_count)

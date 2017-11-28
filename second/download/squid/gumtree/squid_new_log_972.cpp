storeAppendPrintf(e, "\t entries: count: %" PRIu64 " capacity: %" PRIu64 " util: %d%%\n",
                      cd->count,
                      cd->capacity,
                      xpercentInt(cd->count, cd->capacity)
                     );
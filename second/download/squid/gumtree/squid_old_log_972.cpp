storeAppendPrintf(e, "\t entries: count: %d capacity: %d util: %d%%\n",
                      cd->count,
                      cd->capacity,
                      xpercentInt(cd->count, cd->capacity)
                     );
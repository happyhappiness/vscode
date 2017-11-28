storeAppendPrintf(&e, "Current entries: %" PRId64 " %.2f%%\n",
                              currentCount(), (100.0 * currentCount() / entryLimit));
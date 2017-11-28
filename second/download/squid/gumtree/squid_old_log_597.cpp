storeAppendPrintf(sentry, "cd.local_memory = %ld\n",
                      (long) (store_digest ? store_digest->mask_size / 1024 : 0));
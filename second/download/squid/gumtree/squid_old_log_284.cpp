storeAppendPrintf(sentry, "\tMean Object Size:\t%0.2f KB\n",
                      n_disk_objects ? (double) store_swap_size / n_disk_objects : 0.0);
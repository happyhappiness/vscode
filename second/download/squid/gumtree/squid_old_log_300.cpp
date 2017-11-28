storeAppendPrintf(sentry, "\tPage faults with physical i/o: %ld\n",
                      (long)rusage_pagefaults(&rusage));
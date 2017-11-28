storeAppendPrintf(sentry, "\tProcess Data Segment Size via sbrk(): %lu KB\n",
                      (unsigned long) (((char *) sbrk(0) - (char *) sbrk_start) >> 10));
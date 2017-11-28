storeAppendPrintf(s, "start %ld.%06d (%f seconds ago)\n",
                          (long int) http->start_time.tv_sec,
                          (int) http->start_time.tv_usec,
                          tvSubDsec(http->start_time, current_time));
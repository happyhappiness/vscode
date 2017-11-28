logfilePrintf(logfile, "%9ld.%03d %s %s %s\n",
                  (long int) current_time.tv_sec,
                  (int) current_time.tv_usec / 1000,
                  clientip,
                  referer,
                  al->url ? al->url : "-");
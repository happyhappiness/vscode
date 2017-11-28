logfilePrintf(logfile, "%9d.%03d %03d %s %s\n",
                  (int) current_time.tv_sec,
                  (int) current_time.tv_usec / 1000,
                  last_status,
                  RequestMethodStr(request->method),
                  request->canonical);
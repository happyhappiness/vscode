storeAppendPrintf(sentry, "server.http.kbytes_in = %f/sec\n",
                      XAVG(server.http.kbytes_in.kb));
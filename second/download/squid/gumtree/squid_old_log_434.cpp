storeAppendPrintf(sentry, "server.http.kbytes_out = %f/sec\n",
                      XAVG(server.http.kbytes_out.kb));
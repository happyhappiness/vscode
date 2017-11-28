storeAppendPrintf(sentry, "client_http.kbytes_in = %f/sec\n",
                      XAVG(client_http.kbytes_in.kb));
storeAppendPrintf(sentry, "client_http.kbytes_out = %f/sec\n",
                      XAVG(client_http.kbytes_out.kb));
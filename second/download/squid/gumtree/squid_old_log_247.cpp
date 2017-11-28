storeAppendPrintf(sentry, "Last failed connect() at: %s\n",
                              mkhttpdlogtime(&(e->stats.last_connect_failure)));
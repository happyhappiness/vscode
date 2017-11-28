storeAppendPrintf(sentry, "Last failed connect() at: %s\n",
                              Time::FormatHttpd(e->stats.last_connect_failure));
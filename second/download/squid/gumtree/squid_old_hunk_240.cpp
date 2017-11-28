#endif

        }

        if (e->stats.last_connect_failure) {
            storeAppendPrintf(sentry, "Last failed connect() at: %s\n",
                              mkhttpdlogtime(&(e->stats.last_connect_failure)));
        }

        if (e->peer_domain != NULL) {
            storeAppendPrintf(sentry, "DOMAIN LIST: ");

            for (d = e->peer_domain; d; d = d->next) {

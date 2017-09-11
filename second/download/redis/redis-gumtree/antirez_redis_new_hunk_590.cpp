    if (context == NULL || force) {
        if (context != NULL) {
            redisFree(context);
        }

        if (config.hostsocket == NULL) {

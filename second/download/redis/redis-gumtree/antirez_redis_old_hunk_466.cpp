    snprintf(config.prompt+len,sizeof(config.prompt)-len,"> ");
}

static sds getHistoryPath() {
    char *path = NULL;
    sds historyPath = NULL;

    /* check the env for a histfile override */
    path = getenv(REDIS_CLI_HISTFILE_ENV);
    if (path != NULL && *path != '\0') {
        if (!strcmp("/dev/null", path)) {
            return NULL;
        }

        /* if the env is set, return it */
        historyPath = sdscatprintf(sdsempty(), "%s", path);
    } else {
        char *home = getenv("HOME");
        if (home != NULL && *home != '\0') {
            /* otherwise, return the default */
            historyPath = sdscatprintf(sdsempty(), "%s/%s", home, REDIS_CLI_HISTFILE_DEFAULT);
        }
    }

    return historyPath;
}

/*------------------------------------------------------------------------------

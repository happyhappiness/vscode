    return ustime()/1000;
}

static void cliRefreshPrompt(void) {
    int len;

    if (config.hostsocket != NULL)
        len = snprintf(config.prompt,sizeof(config.prompt),"redis %s",
                       config.hostsocket);
    else
        len = snprintf(config.prompt,sizeof(config.prompt),
                       strchr(config.hostip,':') ? "[%s]:%d" : "%s:%d",
                       config.hostip, config.hostport);
    /* Add [dbnum] if needed */
    if (config.dbnum != 0 && config.last_cmd_type != REDIS_REPLY_ERROR)
        len += snprintf(config.prompt+len,sizeof(config.prompt)-len,"[%d]",
            config.dbnum);
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
 * Help functions
 *--------------------------------------------------------------------------- */


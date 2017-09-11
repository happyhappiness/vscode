}

/* Print generic help. */
static void cliOutputGenericHelp() {
    sds version = cliVersion();
    printf(
        "redis-cli %s\r\n"

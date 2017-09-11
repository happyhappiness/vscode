}

/* Print generic help. */
static void cliOutputGenericHelp(void) {
    sds version = cliVersion();
    printf(
        "redis-cli %s\r\n"

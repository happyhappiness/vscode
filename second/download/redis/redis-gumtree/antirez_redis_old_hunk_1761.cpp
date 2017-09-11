
    /* Only use history when stdin is a tty. */
    if (isatty(fileno(stdin))) {
        history = 1;

        if (getenv("HOME") != NULL) {
            historyfile = sdscatprintf(sdsempty(),"%s/.rediscli_history",getenv("HOME"));
            linenoiseHistoryLoad(historyfile);
        }
    }

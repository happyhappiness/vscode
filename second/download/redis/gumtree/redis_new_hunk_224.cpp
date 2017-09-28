    config.interactive = 1;
    linenoiseSetMultiLine(1);
    linenoiseSetCompletionCallback(completionCallback);

    /* Only use history when stdin is a tty. */
    if (isatty(fileno(stdin))) {
        historyfile = getHistoryPath();
        if (historyfile != NULL) {
            history = 1;
            linenoiseHistoryLoad(historyfile);
        }
    }

    cliRefreshPrompt();
    while((line = linenoise(context ? config.prompt : "not connected> ")) != NULL) {

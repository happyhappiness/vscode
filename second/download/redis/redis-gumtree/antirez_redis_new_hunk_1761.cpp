
    /* Only use history when stdin is a tty. */
    if (isatty(fileno(stdin))) {
        historyfile = getHistoryPath();
        if (historyfile != NULL) {
            history = 1;
            linenoiseHistoryLoad(historyfile);
        }
    }

        if (line[0] != '\0') {
            argv = cliSplitArgs(line,&argc);
            if (history) linenoiseHistoryAdd(line);
            printf("HISTORY: %s\n", historyfile);
            if (historyfile) linenoiseHistorySave(historyfile);

            if (argv == NULL) {

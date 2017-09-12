            argv = splitArguments(line,&argc);
            linenoiseHistoryAdd(line);
            if (config.historyfile) linenoiseHistorySave(config.historyfile);
            if (argc > 0) {
                if (strcasecmp(argv[0],"quit") == 0 ||
                    strcasecmp(argv[0],"exit") == 0)
                        exit(0);

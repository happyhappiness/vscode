            fp = stdin;
        } else {
            if ((fp = fopen(filename,"r")) == NULL) {
                serverLog(REDIS_WARNING,
                    "Fatal error, can't open config file '%s'", filename);
                exit(1);
            }

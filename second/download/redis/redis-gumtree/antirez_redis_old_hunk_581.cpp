        } else if (!strcasecmp(argv[0],"e") || !strcasecmp(argv[0],"eval")) {
            ldbEval(lua,argv,argc);
            ldbSendLogs();
        } else if (argc > 1 &&
                   (!strcasecmp(argv[0],"r") || !strcasecmp(argv[0],"redis"))) {
            ldbRedis(lua,argv,argc);

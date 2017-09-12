    config.pubsub_mode = 0;
    config.stdinarg = 0;
    config.auth = NULL;
    config.raw_output = !isatty(fileno(stdout)) && (getenv("FAKETTY") == NULL);
    config.mb_delim = sdsnew("\n");
    cliInitHelp();

    firstarg = parseOptions(argc,argv);
    argc -= firstarg;
    argv += firstarg;

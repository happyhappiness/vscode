                    strcasecmp(argv[0],"exit") == 0)
                {
                    exit(0);
                } else if (argc == 3 && !strcasecmp(argv[0],"connect")) {
                    sdsfree(config.hostip);
                    config.hostip = sdsnew(argv[1]);
                    config.hostport = atoi(argv[2]);
                    cliConnect(1);
                } else {
                    long long start_time = mstime(), elapsed;

                    if (cliSendCommand(argc,argv,1) != REDIS_OK) {
                        cliConnect(1);

                        /* If we still cannot send the command,
                         * print error and abort. */

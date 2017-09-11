                    linenoiseClearScreen();
                } else {
                    long long start_time = mstime(), elapsed;
                    int repeat, skipargs = 0;

                    repeat = atoi(argv[0]);
                    if (repeat) {
                        skipargs = 1;
                    } else {
                        repeat = 1;
                    }

                    if (cliSendCommand(argc-skipargs,argv+skipargs,repeat)
                        != REDIS_OK)
                    {
                        cliConnect(1);

                        /* If we still cannot send the command print error.
                         * We'll try to reconnect the next time. */
                        if (cliSendCommand(argc,argv,1) != REDIS_OK)
                            cliPrintContextError();
                    }

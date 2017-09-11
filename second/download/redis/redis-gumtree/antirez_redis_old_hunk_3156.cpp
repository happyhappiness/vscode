                    linenoiseClearScreen();
                } else {
                    long long start_time = mstime(), elapsed;

                    if (cliSendCommand(argc,argv,1) != REDIS_OK) {
                        cliConnect(1);

                        /* If we still cannot send the command,
                         * print error and abort. */
                        if (cliSendCommand(argc,argv,1) != REDIS_OK)
                            cliPrintContextError();
                    }

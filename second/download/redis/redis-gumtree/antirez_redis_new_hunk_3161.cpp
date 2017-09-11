                        /* If we still cannot send the command,
                         * print error and abort. */
                        if (cliSendCommand(argc,argv,1) != REDIS_OK)
                            cliPrintContextError();
                    }
                    elapsed = mstime()-start_time;
                    if (elapsed >= 500) {

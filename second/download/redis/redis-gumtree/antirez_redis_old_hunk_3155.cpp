
                        /* If we still cannot send the command print error.
                         * We'll try to reconnect the next time. */
                        if (cliSendCommand(argc,argv,1) != REDIS_OK)
                            cliPrintContextError();
                    }
                    elapsed = mstime()-start_time;

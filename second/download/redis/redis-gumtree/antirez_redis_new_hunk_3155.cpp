
                        /* If we still cannot send the command print error.
                         * We'll try to reconnect the next time. */
                        if (cliSendCommand(argc-skipargs,argv+skipargs,repeat)
                            != REDIS_OK)
                            cliPrintContextError();
                    }
                    elapsed = mstime()-start_time;

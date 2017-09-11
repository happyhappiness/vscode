                        repeat = 1;
                    }

                    while (1) {
                        config.cluster_reissue_command = 0;
                        if (cliSendCommand(argc-skipargs,argv+skipargs,repeat)
                            != REDIS_OK)
                        {
                            cliConnect(1);

                            /* If we still cannot send the command print error.
                             * We'll try to reconnect the next time. */
                            if (cliSendCommand(argc-skipargs,argv+skipargs,repeat)
                                != REDIS_OK)
                                cliPrintContextError();
                        }
                        /* Issue the command again if we got redirected in cluster mode */
                        if (config.cluster_mode && config.cluster_reissue_command) {
                            cliConnect(1);
                        } else {
                            break;
                        }
                    }
                    elapsed = mstime()-start_time;
                    if (elapsed >= 500) {

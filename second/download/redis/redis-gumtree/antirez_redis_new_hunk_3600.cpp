                {
                    exit(0);
                } else {
                    long long start_time = mstime(), elapsed;

                    if (cliSendCommand(argc,argv,1) != REDIS_OK) {
                        printf("Reconnecting... ");
                        fflush(stdout);
                        if (cliConnect(1) != REDIS_OK) exit(1);
                        printf("OK\n");

                        /* If we still cannot send the command,
                         * print error and abort. */
                        if (cliSendCommand(argc,argv,1) != REDIS_OK)
                            cliPrintContextErrorAndExit();
                    }
                    elapsed = mstime()-start_time;
                    if (elapsed > 500) printf("%.2f seconds\n",

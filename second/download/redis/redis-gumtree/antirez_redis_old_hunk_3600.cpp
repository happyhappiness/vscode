                {
                    exit(0);
                } else {
                    int err;
                    long long start_time = mstime(), elapsed;

                    if ((err = cliSendCommand(argc, argv, 1)) != 0) {
                        if (err == ECONNRESET) {
                            printf("Reconnecting... ");
                            fflush(stdout);
                            if (cliConnect(1) == -1) exit(1);
                            printf("OK\n");
                            cliSendCommand(argc,argv,1);
                        }
                    }
                    elapsed = mstime()-start_time;
                    if (elapsed > 500) printf("%.2f seconds\n",

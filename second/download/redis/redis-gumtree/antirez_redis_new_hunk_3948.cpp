            if (argc > 0) {
                if (strcasecmp(argv[0],"quit") == 0 ||
                    strcasecmp(argv[0],"exit") == 0)
                {
                    exit(0);
                } else {
                    int err;

                    if ((err = cliSendCommand(argc, argv, 1)) != 0) {
                        if (err == ECONNRESET) {
                            printf("Reconnecting... ");
                            fflush(stdout);
                            if (cliConnect(1) == -1) exit(1);
                            printf("OK\n");
                            cliSendCommand(argc,argv,1);
                        }
                    }
                }
            }
            /* Free the argument vector */
            for (j = 0; j < argc; j++)

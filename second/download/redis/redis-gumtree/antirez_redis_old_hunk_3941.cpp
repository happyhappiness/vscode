            } else if (argc > 0) {
                if (strcasecmp(argv[0],"quit") == 0 ||
                    strcasecmp(argv[0],"exit") == 0)
                        exit(0);
                else
                    cliSendCommand(argc, argv, 1);
            }
            /* Free the argument vector */
            for (j = 0; j < argc; j++)

            config.auth = argv[i+1];
            i++;
        } else if (!strcmp(argv[i],"-i")) {
            fprintf(stderr,
"Starting interactive mode using -i is deprecated. Interactive mode is started\n"
"by default when redis-cli is executed without a command to execute.\n"
            );
        } else if (!strcmp(argv[i],"-c")) {
            config.argn_from_stdin = 1;
        } else if (!strcmp(argv[i],"-v")) {

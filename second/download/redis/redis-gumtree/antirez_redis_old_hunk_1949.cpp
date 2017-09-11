            cfg.unix.path = argv[0];
        } else if (argc >= 1 && !strcmp(argv[0],"--skip-throughput")) {
            throughput = 0;
        } else {
            fprintf(stderr, "Invalid argument: %s\n", argv[0]);
            exit(1);

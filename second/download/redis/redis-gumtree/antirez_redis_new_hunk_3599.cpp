        int lastarg = i==argc-1;

        if (!strcmp(argv[i],"-h") && !lastarg) {
            config.hostip = argv[i+1];
            i++;
        } else if (!strcmp(argv[i],"-h") && lastarg) {
            usage();

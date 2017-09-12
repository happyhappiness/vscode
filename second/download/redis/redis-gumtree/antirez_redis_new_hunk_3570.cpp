            config.keepalive = atoi(argv[i+1]);
            i++;
        } else if (!strcmp(argv[i],"-h") && !lastarg) {
            config.hostip = argv[i+1];
            i++;
        } else if (!strcmp(argv[i],"-p") && !lastarg) {
            config.hostport = atoi(argv[i+1]);


    if (argv[var][0] == '-') {
        if (argv[var][1] == '4')
            prefer = AF_INET;
        else if (argv[var][1] == '6')
            prefer = AF_INET6;
        else if (argv[var][1] == 'E')
            edns_max = atoi(argv[var++]);
        else {
            fprintf(stderr, "usage: %s [-6|-4] [-E packet-size] ip port\n", argv[0]);
            fprintf(stderr, "  EDNS packets my be up to %d\n", PACKET_BUFSZ);
            return 1;
        }

        var++;
    }


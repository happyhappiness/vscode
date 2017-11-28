
    if (argv[var][0] == '-') {
        if (argv[var][1] == '4')
            prefer = AF_INET;
        else if (argv[var][1] == '6')
            prefer = AF_INET6;
        else {
            fprintf(stderr, "usage: %s [-6|-4] ip port\n", argv[0]);
            return 1;
        }

        var++;
    }


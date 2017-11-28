
#endif

    }
    loops = ping ? pcount : 1;

    for (i = 0; loops == 0 || i < loops; i++) {
        int fsize = 0;
        struct addrinfo *AI = NULL;

        if (opt_verbose)
            fprintf(stderr, "Resolving... %s\n", hostname);


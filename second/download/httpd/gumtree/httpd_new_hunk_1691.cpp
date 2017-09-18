
    {
        /* get server information */
        struct hostent *he;
        he = gethostbyname(hostname);
        if (!he)
            err("bad hostname");
        server.sin_family = he->h_addrtype;
        server.sin_port = htons(port);
        server.sin_addr.s_addr = ((unsigned long *) (he->h_addr_list[0]))[0];
    }

    con = malloc(concurrency * sizeof(struct connection));

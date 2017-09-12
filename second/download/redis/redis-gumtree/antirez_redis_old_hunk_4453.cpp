    parseOptions(argc,argv);

    if (config.keepalive == 0) {
        printf("WARNING: keepalive disabled, you probably need 'echo 1 > /proc/sys/net/ipv4/tcp_tw_reuse' in order to use a lot of clients/requests\n");
    }

    do {

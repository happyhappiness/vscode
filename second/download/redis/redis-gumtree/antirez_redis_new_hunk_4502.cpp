    for(j = 0; j < argc; j++)
        argvcopy[j] = sdsnew(argv[j]);

    if (argc < 1) {
        fprintf(stderr, "usage: redis-cli [-h host] [-p port] cmd arg1 arg2 arg3 ... argN\n");
        fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-p port] cmd arg1 arg2 ... arg(N-1)\n");

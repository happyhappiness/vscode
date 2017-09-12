        argvcopy[j] = sdsnew(argv[j]);

    if (argc < 1) {
        fprintf(stderr, "usage: redis-cli [-h host] [-p port] [-r repeat_times] [-n db_num] cmd arg1 arg2 arg3 ... argN\n");
        fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-p port] [-r repeat_times] [-n db_num] cmd arg1 arg2 ... arg(N-1)\n");
        fprintf(stderr, "\nIf a pipe from standard input is detected this data is used as last argument.\n\n");
        fprintf(stderr, "example: cat /etc/passwd | redis-cli set my_passwd\n");
        fprintf(stderr, "example: redis-cli get my_passwd\n");

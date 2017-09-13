int main(int argc, char **argv) {
    int firstarg, j;
    char **argvcopy;
    struct redisCommand *rc;

    config.hostip = "127.0.0.1";
    config.hostport = 6379;
    config.repeat = 1;

    firstarg = parseOptions(argc,argv);
    argc -= firstarg;
    argv += firstarg;
    
    /* Turn the plain C strings into Sds strings */
    argvcopy = zmalloc(sizeof(char*)*argc+1);
    for(j = 0; j < argc; j++)
        argvcopy[j] = sdsnew(argv[j]);

    if (argc < 1) {
        fprintf(stderr, "usage: redis-cli [-h host] [-p port] [-r repeat_times] cmd arg1 arg2 arg3 ... argN\n");
        fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-p port] -r [repeat_times] cmd arg1 arg2 ... arg(N-1)\n");
        fprintf(stderr, "\nIf a pipe from standard input is detected this data is used as last argument.\n\n");
        fprintf(stderr, "example: cat /etc/passwd | redis-cli set my_passwd\n");
        fprintf(stderr, "example: redis-cli get my_passwd\n");
        fprintf(stderr, "example: redis-cli -r 100 lpush mylist x\n");
        exit(1);
    }

    /* Read the last argument from stdandard input if needed */
    if ((rc = lookupCommand(argv[0])) != NULL) {
        if (rc->arity > 0 && argc == rc->arity-1) {
            sds lastarg = readArgFromStdin();
            argvcopy[argc] = lastarg;
            argc++;
        }
    }

    return cliSendCommand(argc, argvcopy);
}
int main(int argc, char **argv) {
    int firstarg, j;
    char **argvcopy;
    struct redisCommand *rc;

    config.hostip = "127.0.0.1";
    config.hostport = 6379;
    config.repeat = 1;
    config.dbnum = 0;

    firstarg = parseOptions(argc,argv);
    argc -= firstarg;
    argv += firstarg;
    
    /* Turn the plain C strings into Sds strings */
    argvcopy = zmalloc(sizeof(char*)*argc+1);
    for(j = 0; j < argc; j++)
        argvcopy[j] = sdsnew(argv[j]);

    if (argc < 1) usage();

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
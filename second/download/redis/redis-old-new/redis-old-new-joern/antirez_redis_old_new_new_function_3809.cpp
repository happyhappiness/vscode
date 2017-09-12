int main(int argc, char **argv) {
    int firstarg;
    char **argvcopy;

    config.hostip = "127.0.0.1";
    config.hostport = 6379;
    config.repeat = 1;
    config.dbnum = 0;
    config.argn_from_stdin = 0;
    config.shutdown = 0;
    config.interactive = 0;
    config.monitor_mode = 0;
    config.pubsub_mode = 0;
    config.raw_output = 0;
    config.auth = NULL;
    config.historyfile = NULL;

    if (getenv("HOME") != NULL) {
        config.historyfile = malloc(256);
        snprintf(config.historyfile,256,"%s/.rediscli_history",getenv("HOME"));
        linenoiseHistoryLoad(config.historyfile);
    }

    firstarg = parseOptions(argc,argv);
    argc -= firstarg;
    argv += firstarg;

    if (config.auth != NULL) {
        char *authargv[2];

        authargv[0] = "AUTH";
        authargv[1] = config.auth;
        cliSendCommand(2, convertToSds(2, authargv), 1);
    }

    if (argc == 0 || config.interactive == 1) repl();

    argvcopy = convertToSds(argc+1, argv);
    if (config.argn_from_stdin) {
        sds lastarg = readArgFromStdin();
        argvcopy[argc] = lastarg;
        argc++;
    }
    return cliSendCommand(argc, argvcopy, config.repeat);
}
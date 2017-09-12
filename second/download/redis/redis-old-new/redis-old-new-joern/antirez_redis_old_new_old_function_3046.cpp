int main(int argc, char **argv) {
    int firstarg;

    config.hostip = sdsnew("127.0.0.1");
    config.hostport = 6379;
    config.hostsocket = NULL;
    config.repeat = 1;
    config.dbnum = 0;
    config.interactive = 0;
    config.shutdown = 0;
    config.monitor_mode = 0;
    config.pubsub_mode = 0;
    config.stdinarg = 0;
    config.auth = NULL;
    config.historyfile = NULL;
    config.raw_output = !isatty(fileno(stdout)) && (getenv("FAKETTY") == NULL);
    config.mb_delim = sdsnew("\n");
    cliInitHelp();

    if (getenv("HOME") != NULL) {
        config.historyfile = malloc(256);
        snprintf(config.historyfile,256,"%s/.rediscli_history",getenv("HOME"));
        linenoiseHistoryLoad(config.historyfile);
    }

    firstarg = parseOptions(argc,argv);
    argc -= firstarg;
    argv += firstarg;

    /* Try to connect */
    if (cliConnect(0) != REDIS_OK) exit(1);

    /* Start interactive mode when no command is provided */
    if (argc == 0) repl();
    /* Otherwise, we have some arguments to execute */
    return noninteractive(argc,convertToSds(argc,argv));
}
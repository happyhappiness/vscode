    return REDIS_OK;
}

static int cliSendCommand(int argc, char **argv, int repeat) {
    char *command = argv[0];
    size_t *argvlen;
    int j;

    config.raw_output = !strcasecmp(command,"info");
    if (!strcasecmp(command,"help")) {
        output_help(--argc, ++argv);
        return REDIS_OK;
    }
    if (!strcasecmp(command,"shutdown")) config.shutdown = 1;

    return 0;
}

static int cliSendCommand(int argc, char **argv, int repeat) {
    char *command = argv[0];
    int fd, j, retval = 0;
    sds cmd;

    config.raw_output = !strcasecmp(command,"info");
    if (!strcasecmp(command,"help")) {
        output_help(--argc, ++argv);
        return 0;
    }
    if (!strcasecmp(command,"shutdown")) config.shutdown = 1;

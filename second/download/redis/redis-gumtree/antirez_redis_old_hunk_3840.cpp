    return 0;
}

static int cliSendCommand(int argc, char **argv, int repeat) {
    char *command = argv[0];
    int fd, j, retval = 0;
    sds cmd;

    config.raw_output = !strcasecmp(command,"info");
    if (!strcasecmp(command,"shutdown")) config.shutdown = 1;
    if (!strcasecmp(command,"monitor")) config.monitor_mode = 1;
    if (!strcasecmp(command,"subscribe") ||

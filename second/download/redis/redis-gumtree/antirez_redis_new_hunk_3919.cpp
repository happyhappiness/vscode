    return 0;
}

static void showInteractiveHelp(void) {
    printf(
    "\n"
    "Welcome to redis-cli " REDIS_VERSION "!\n"
    "Just type any valid Redis command to see a pretty printed output.\n"
    "\n"
    "It is possible to quote strings, like in:\n"
    "  set \"my key\" \"some string \\xff\\n\"\n"
    "\n"
    "You can find a list of valid Redis commands at\n"
    "  http://code.google.com/p/redis/wiki/CommandReference\n"
    "\n"
    "Note: redis-cli supports line editing, use up/down arrows for history."
    "\n\n");
}

static int cliSendCommand(int argc, char **argv, int repeat) {
    char *command = argv[0];
    int fd, j, retval = 0;
    sds cmd;

    config.raw_output = !strcasecmp(command,"info");
    if (!strcasecmp(command,"help")) {
        showInteractiveHelp();
        return 0;
    }
    if (!strcasecmp(command,"shutdown")) config.shutdown = 1;
    if (!strcasecmp(command,"monitor")) config.monitor_mode = 1;
    if (!strcasecmp(command,"subscribe") ||

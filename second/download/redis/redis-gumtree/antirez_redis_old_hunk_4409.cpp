    }
}

static int cliSendCommand(int argc, char **argv) {
    struct redisCommand *rc = lookupCommand(argv[0]);
    int fd, j, retval = 0;

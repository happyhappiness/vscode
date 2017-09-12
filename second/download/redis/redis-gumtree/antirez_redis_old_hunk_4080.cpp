}

static int cliSendCommand(int argc, char **argv, int repeat) {
    struct redisCommand *rc = lookupCommand(argv[0]);
    int fd, j, retval = 0;
    sds cmd;

    if (!rc) {
        fprintf(stderr,"Unknown command '%s'\n",argv[0]);
        return 1;
    }
    config.raw_output = (rc->flags & CMDFLAG_RAWOUTPUT);

    if ((rc->arity > 0 && argc != rc->arity) ||
        (rc->arity < 0 && argc < -rc->arity)) {
            fprintf(stderr,"Wrong number of arguments for '%s'\n",rc->name);
            return 1;
    }

    if (!strcasecmp(rc->name,"shutdown")) config.shutdown = 1;
    if (!strcasecmp(rc->name,"monitor")) config.monitor_mode = 1;
    if (!strcasecmp(rc->name,"subscribe") ||
        !strcasecmp(rc->name,"psubscribe")) config.pubsub_mode = 1;
    if ((fd = cliConnect()) == -1) return 1;

    /* Select db number */

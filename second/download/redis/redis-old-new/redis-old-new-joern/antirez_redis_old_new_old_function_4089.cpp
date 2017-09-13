static int cliSendCommand(int argc, char **argv, int repeat) {
    struct redisCommand *rc = lookupCommand(argv[0]);
    int fd, j, retval = 0;
    sds cmd;

    if (!rc) {
        fprintf(stderr,"Unknown command '%s'\n",argv[0]);
        return 1;
    }

    if ((rc->arity > 0 && argc != rc->arity) ||
        (rc->arity < 0 && argc < -rc->arity)) {
            fprintf(stderr,"Wrong number of arguments for '%s'\n",rc->name);
            return 1;
    }
    if (!strcasecmp(rc->name,"monitor")) config.monitor_mode = 1;
    if (!strcasecmp(rc->name,"subscribe") ||
        !strcasecmp(rc->name,"psubscribe")) config.pubsub_mode = 1;
    if ((fd = cliConnect()) == -1) return 1;

    /* Select db number */
    retval = selectDb(fd);
    if (retval) {
        fprintf(stderr,"Error setting DB num\n");
        return 1;
    }

    while(repeat--) {
        /* Build the command to send */
        cmd = sdsempty();
        if (rc->flags & REDIS_CMD_MULTIBULK) {
            cmd = sdscatprintf(cmd,"*%d\r\n",argc);
            for (j = 0; j < argc; j++) {
                cmd = sdscatprintf(cmd,"$%lu\r\n",
                    (unsigned long)sdslen(argv[j]));
                cmd = sdscatlen(cmd,argv[j],sdslen(argv[j]));
                cmd = sdscatlen(cmd,"\r\n",2);
            }
        } else {
            for (j = 0; j < argc; j++) {
                if (j != 0) cmd = sdscat(cmd," ");
                if (j == argc-1 && rc->flags & REDIS_CMD_BULK) {
                    cmd = sdscatprintf(cmd,"%lu",
                        (unsigned long)sdslen(argv[j]));
                } else {
                    cmd = sdscatlen(cmd,argv[j],sdslen(argv[j]));
                }
            }
            cmd = sdscat(cmd,"\r\n");
            if (rc->flags & REDIS_CMD_BULK) {
                cmd = sdscatlen(cmd,argv[argc-1],sdslen(argv[argc-1]));
                cmd = sdscatlen(cmd,"\r\n",2);
            }
        }
        anetWrite(fd,cmd,sdslen(cmd));
        sdsfree(cmd);

        while (config.monitor_mode) {
            cliReadSingleLineReply(fd,0);
        }

        if (config.pubsub_mode) {
            printf("Reading messages... (press Ctrl-c to quit)\n");
            while (1) {
                cliReadReply(fd);
                printf("\n");
            }
        }

        retval = cliReadReply(fd);
        if (retval) {
            return retval;
        }
    }
    return 0;
}
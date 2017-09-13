static int cliSendCommand(int argc, char **argv) {
    struct redisCommand *rc = lookupCommand(argv[0]);
    int fd, j, retval = 0;
    sds cmd = sdsempty();

    if (!rc) {
        fprintf(stderr,"Unknown command '%s'\n",argv[0]);
        return 1;
    }

    if ((rc->arity > 0 && argc != rc->arity) ||
        (rc->arity < 0 && argc < -rc->arity)) {
            fprintf(stderr,"Wrong number of arguments for '%s'\n",rc->name);
            return 1;
    }
    if ((fd = cliConnect()) == -1) return 1;

    /* Build the command to send */
    for (j = 0; j < argc; j++) {
        if (j != 0) cmd = sdscat(cmd," ");
        if (j == argc-1 && rc->flags & REDIS_CMD_BULK) {
            cmd = sdscatprintf(cmd,"%d",sdslen(argv[j]));
        } else {
            cmd = sdscatlen(cmd,argv[j],sdslen(argv[j]));
        }
    }
    cmd = sdscat(cmd,"\r\n");
    if (rc->flags & REDIS_CMD_BULK) {
        cmd = sdscatlen(cmd,argv[argc-1],sdslen(argv[argc-1]));
        cmd = sdscat(cmd,"\r\n");
    }
    anetWrite(fd,cmd,sdslen(cmd));
    retval = cliReadReply(fd);
    if (retval) {
        close(fd);
        return retval;
    }
    close(fd);
    return 0;
}
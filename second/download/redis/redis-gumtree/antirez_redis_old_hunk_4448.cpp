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

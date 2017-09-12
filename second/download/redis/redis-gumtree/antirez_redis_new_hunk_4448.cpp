    if ((fd = cliConnect()) == -1) return 1;

    /* Build the command to send */
    if (rc->flags & REDIS_CMD_MULTIBULK) {
        cmd = sdscatprintf(cmd,"*%d\r\n",argc);
        for (j = 0; j < argc; j++) {
            cmd = sdscatprintf(cmd,"$%d\r\n",sdslen(argv[j]));
            cmd = sdscatlen(cmd,argv[j],sdslen(argv[j]));
            cmd = sdscatlen(cmd,"\r\n",2);
        }
    } else {
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
            cmd = sdscatlen(cmd,"\r\n",2);
        }
    }
    anetWrite(fd,cmd,sdslen(cmd));
    retval = cliReadReply(fd);

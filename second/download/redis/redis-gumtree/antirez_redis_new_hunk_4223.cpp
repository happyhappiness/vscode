    int retval = 1;
    sds cmd;
    char type;
    if (config.authpw[0] != '\0') {
        cmd = sdsempty();
        cmd = sdscatprintf(cmd,"AUTH %s\r\n",config.authpw);
        anetWrite(fd,cmd,sdslen(cmd));
        anetRead(fd,&type,1);
        if (type == '+') 
            retval = 0;
        int ret2 = cliReadSingleLineReply(fd,1);
        if (ret2)
            close(fd);
    } else {
        retval = 0;
    }

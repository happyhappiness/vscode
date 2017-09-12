        return 1;
    }

    while(repeat--) {
        /* Build the command to send */
        cmd = sdscatprintf(sdsempty(),"*%d\r\n",argc);
        for (j = 0; j < argc; j++) {
            cmd = sdscatprintf(cmd,"$%lu\r\n",
                (unsigned long)sdslen(argv[j]));
            cmd = sdscatlen(cmd,argv[j],sdslen(argv[j]));
            cmd = sdscatlen(cmd,"\r\n",2);
        }
        anetWrite(fd,cmd,sdslen(cmd));
        sdsfree(cmd);

        while (config.monitor_mode) {
            cliReadSingleLineReply(fd,0);
        }

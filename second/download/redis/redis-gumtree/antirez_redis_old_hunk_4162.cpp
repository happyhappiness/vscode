        anetWrite(fd,cmd,sdslen(cmd));
        sdsfree(cmd);

        while (read_forever) {
            cliReadSingleLineReply(fd,0);
        }

        retval = cliReadReply(fd);
        if (retval) {
            return retval;

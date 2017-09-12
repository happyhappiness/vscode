    while(repeat--) {
        anetWrite(fd,cmd,sdslen(cmd));
        while (config.monitor_mode) {
            cliReadSingleLineReply(fd,0);
        }

        if (config.pubsub_mode) {

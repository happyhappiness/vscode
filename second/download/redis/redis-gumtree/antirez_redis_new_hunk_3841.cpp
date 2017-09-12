    while(repeat--) {
        anetWrite(fd,cmd,sdslen(cmd));
        while (config.monitor_mode) {
            if (cliReadSingleLineReply(fd,0)) exit(1);
            printf("\n");
        }

        if (config.pubsub_mode) {

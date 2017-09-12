    while(repeat--) {
        anetWrite(fd,cmd,sdslen(cmd));
        while (config.monitor_mode) {
            if (cliReadSingleLineReply(fd,0)) exit(1);
            printf("\n");
        }

        if (config.pubsub_mode) {
            printf("Reading messages... (press Ctrl-c to quit)\n");
            while (1) {
                cliReadReply(fd);
                printf("\n\n");
            }
        }

        retval = cliReadReply(fd);
        if (!config.raw_output && config.tty) printf("\n");
        if (retval) return retval;
    }
    return 0;
}

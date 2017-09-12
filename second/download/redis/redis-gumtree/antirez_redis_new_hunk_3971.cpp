    }
    switch(type) {
    case '-':
        if (config.tty) printf("(error) ");
        cliReadSingleLineReply(fd,0);
        return 1;
    case '+':
        return cliReadSingleLineReply(fd,0);
    case ':':
        if (config.tty) printf("(integer) ");
        return cliReadSingleLineReply(fd,0);
    case '$':
        return cliReadBulkReply(fd);

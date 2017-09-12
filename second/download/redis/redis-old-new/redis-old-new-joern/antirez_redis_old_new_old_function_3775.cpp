static int cliReadReply(int fd) {
    char type;

    if (anetRead(fd,&type,1) <= 0) {
        if (config.shutdown) return 0;
        exit(1);
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
    case '*':
        return cliReadMultiBulkReply(fd);
    default:
        printf("protocol error, got '%c' as reply type byte\n", type);
        return 1;
    }
}
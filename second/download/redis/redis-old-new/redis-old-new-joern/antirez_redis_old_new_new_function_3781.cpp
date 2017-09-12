static int cliReadReply(int fd) {
    char type;
    int nread;

    if ((nread = anetRead(fd,&type,1)) <= 0) {
        if (config.shutdown) return 0;
        if (config.interactive &&
            (nread == 0 || (nread == -1 && errno == ECONNRESET)))
        {
            return ECONNRESET;
        } else {
            printf("I/O error while reading from socket: %s",strerror(errno));
            exit(1);
        }
    }
    switch(type) {
    case '-':
        printf("(error) ");
        cliReadSingleLineReply(fd,0);
        return 1;
    case '+':
        return cliReadSingleLineReply(fd,0);
    case ':':
        printf("(integer) ");
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
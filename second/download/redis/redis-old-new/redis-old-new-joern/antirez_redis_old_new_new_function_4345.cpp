static int cliReadReply(int fd) {
    char type;

    if (anetRead(fd,&type,1) <= 0) exit(1);
    switch(type) {
    case '-':
        printf("(error) ");
        cliReadSingleLineReply(fd);
        return 1;
    case '+':
    case ':':
        printf("(integer) ");
        return cliReadSingleLineReply(fd);
    case '$':
        return cliReadBulkReply(fd);
    case '*':
        return cliReadMultiBulkReply(fd);
    default:
        printf("protocol error, got '%c' as reply type byte\n", type);
        return 1;
    }
}
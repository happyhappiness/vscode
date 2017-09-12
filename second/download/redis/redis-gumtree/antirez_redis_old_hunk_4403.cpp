    switch(type) {
    case '-':
        printf("(error) ");
        cliReadSingleLineReply(fd);
        return 1;
    case '+':
        return cliReadSingleLineReply(fd);
    case ':':
        printf("(integer) ");
        return cliReadSingleLineReply(fd);
    case '$':
        return cliReadBulkReply(fd);
    case '*':

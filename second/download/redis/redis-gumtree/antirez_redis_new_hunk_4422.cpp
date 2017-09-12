        return 1;
    case '+':
    case ':':
        printf("(integer) ");
        return cliReadSingleLineReply(fd);
    case '$':
        return cliReadBulkReply(fd);

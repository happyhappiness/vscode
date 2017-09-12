        return 1;
    case '+':
    case ':':
        return cliReadSingleLineReply(fd);
    case '$':
        return cliReadBulkReply(fd);

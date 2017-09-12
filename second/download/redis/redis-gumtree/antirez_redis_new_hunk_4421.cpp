        cliReadSingleLineReply(fd);
        return 1;
    case '+':
        return cliReadSingleLineReply(fd);
    case ':':
        printf("(integer) ");
        return cliReadSingleLineReply(fd);

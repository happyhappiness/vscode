        cliReadSingleLineReply(fd);
        return 1;
    case '+':
    case ':':
        printf("(integer) ");
        return cliReadSingleLineReply(fd);

    return sdstrim(line,"\r\n");
}

static int cliReadInlineReply(int fd, int type) {
    sds reply = cliReadLine(fd);

    if (reply == NULL) return 1;
    printf("%s\n", reply);
    if (type == REDIS_CMD_SINGLELINEREPLY) return 0;
    if (type == REDIS_CMD_INTREPLY) return atoi(reply) < 0;
    if (type == REDIS_CMD_RETCODEREPLY) return reply[0] == '-';
    return 0;
}

static int cliReadBulkReply(int fd, int multibulk) {
    sds replylen = cliReadLine(fd);
    char *reply, crlf[2];
    int bulklen, error = 0;

    if (replylen == NULL) return 1;
    if (strcmp(replylen,"nil") == 0) {
        sdsfree(replylen);
        printf("(nil)\n");
        return 0;
    }
    bulklen = atoi(replylen);
    if (multibulk && bulklen == -1) {
        sdsfree(replylen);
        printf("(nil)");
        return 0;
    }
    if (bulklen < 0) {
        bulklen = -bulklen;
        error = 1;
    }
    reply = zmalloc(bulklen);
    anetRead(fd,reply,bulklen);
    anetRead(fd,crlf,2);
    if (bulklen && fwrite(reply,bulklen,1,stdout) == 0) {
        zfree(reply);
        return 1;
    }
    if (!multibulk && isatty(fileno(stdout)) && reply[bulklen-1] != '\n')
        printf("\n");
    zfree(reply);
    return error;
}

static int cliReadMultiBulkReply(int fd) {
    sds replylen = cliReadLine(fd);
    int elements, c = 1;

    if (replylen == NULL) return 1;
    if (strcmp(replylen,"nil") == 0) {
        sdsfree(replylen);
        printf("(nil)\n");
        return 0;
    }
    elements = atoi(replylen);
    while(elements--) {
        printf("%d. ", c);
        if (cliReadBulkReply(fd,1)) return 1;
        printf("\n");
        c++;
    }
    return 0;
}

static int cliSendCommand(int argc, char **argv) {
    struct redisCommand *rc = lookupCommand(argv[0]);
    int fd, j, retval = 0;

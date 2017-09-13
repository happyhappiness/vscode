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
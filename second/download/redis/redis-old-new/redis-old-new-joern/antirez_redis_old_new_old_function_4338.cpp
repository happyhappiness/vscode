static int cliReadBulkReply(int fd) {
    sds replylen = cliReadLine(fd);
    char *reply, crlf[2];
    int bulklen;

    if (replylen == NULL) return 1;
    bulklen = atoi(replylen);
    if (bulklen == -1) {
        sdsfree(replylen);
        printf("(nil)");
        return 0;
    }
    reply = zmalloc(bulklen);
    anetRead(fd,reply,bulklen);
    anetRead(fd,crlf,2);
    if (bulklen && fwrite(reply,bulklen,1,stdout) == 0) {
        zfree(reply);
        return 1;
    }
    if (isatty(fileno(stdout)) && reply[bulklen-1] != '\n')
        printf("\n");
    zfree(reply);
    return 0;
}
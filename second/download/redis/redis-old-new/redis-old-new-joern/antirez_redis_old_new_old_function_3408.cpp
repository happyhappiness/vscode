static int cliReadBulkReply(int fd) {
    sds replylen = cliReadLine(fd);
    char *reply, crlf[2];
    int bulklen;

    if (replylen == NULL) return 1;
    bulklen = atoi(replylen);
    if (bulklen == -1) {
        sdsfree(replylen);
        printf("(nil)\n");
        return 0;
    }
    reply = zmalloc(bulklen);
    anetRead(fd,reply,bulklen);
    anetRead(fd,crlf,2);
    if (config.raw_output || !config.tty) {
        if (bulklen && fwrite(reply,bulklen,1,stdout) == 0) {
            zfree(reply);
            return 1;
        }
    } else {
        /* If you are producing output for the standard output we want
         * a more interesting output with quoted characters and so forth */
        printStringRepr(reply,bulklen);
    }
    zfree(reply);
    return 0;
}
static int cliReadMultiBulkReply(int fd) {
    sds replylen = cliReadLine(fd);
    int elements, c = 1;

    if (replylen == NULL) return 1;
    elements = atoi(replylen);
    if (elements == -1) {
        sdsfree(replylen);
        printf("(nil)\n");
        return 0;
    }
    if (elements == 0) {
        printf("(empty list or set)\n");
    }
    while(elements--) {
        if (config.tty) printf("%d. ", c);
        if (cliReadReply(fd)) return 1;
        if (elements) printf("%c",config.mb_sep);
        c++;
    }
    return 0;
}
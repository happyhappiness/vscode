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
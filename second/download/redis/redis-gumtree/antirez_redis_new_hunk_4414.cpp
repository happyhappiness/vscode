    bulklen = atoi(replylen);
    if (bulklen == -1) {
        sdsfree(replylen);
        printf("(nil)\n");
        return 0;
    }
    reply = zmalloc(bulklen);

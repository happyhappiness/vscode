    bulklen = atoi(replylen);
    if (bulklen == -1) {
        sdsfree(replylen);
        printf("(nil)");
        return 0;
    }
    reply = zmalloc(bulklen);

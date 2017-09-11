        minidx = 2; maxidx = 3;
    }

    if (zslParseLexRange(c->argv[minidx],c->argv[maxidx],&range) != REDIS_OK) {
        addReplyError(c,"min or max not valid string range item");
        return;
    }

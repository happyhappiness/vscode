    if (!dstkey) {
        decrRefCount(dstset);
    } else {
        addReply(c,shared.ok);
        server.dirty++;
    }
    zfree(dv);

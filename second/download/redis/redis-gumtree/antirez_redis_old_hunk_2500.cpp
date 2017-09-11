    } else {
        decrRefCount(dstobj);
        addReply(c,shared.czero);
    }
    zfree(src);
}

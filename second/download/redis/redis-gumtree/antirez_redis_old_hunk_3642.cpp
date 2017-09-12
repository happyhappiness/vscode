    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
        decrRefCount(o);
        return;
    }
    decrRefCount(o);
    addReply(c,shared.ok);
    return;

badfmt: /* Bad format errors */
    addReplyErrorFormat(c,"Invalid argument '%s' for CONFIG SET '%s'",
            (char*)o->ptr,
            (char*)c->argv[2]->ptr);
    decrRefCount(o);
}

void configGetCommand(redisClient *c) {
    robj *o = getDecodedObject(c->argv[2]);
    void *replylen = addDeferredMultiBulkLength(c);
    char *pattern = o->ptr;
    int matches = 0;

    if (stringmatch(pattern,"dbfilename",0)) {
        addReplyBulkCString(c,"dbfilename");

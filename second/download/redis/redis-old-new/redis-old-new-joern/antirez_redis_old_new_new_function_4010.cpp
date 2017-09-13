static void configGetCommand(redisClient *c) {
    robj *o = getDecodedObject(c->argv[2]);
    robj *lenobj = createObject(REDIS_STRING,NULL);
    char *pattern = o->ptr;
    int matches = 0;

    addReply(c,lenobj);
    decrRefCount(lenobj);

    if (stringmatch(pattern,"dbfilename",0)) {
        addReplyBulkCString(c,"dbfilename");
        addReplyBulkCString(c,server.dbfilename);
        matches++;
    }
    if (stringmatch(pattern,"requirepass",0)) {
        addReplyBulkCString(c,"requirepass");
        addReplyBulkCString(c,server.requirepass);
        matches++;
    }
    if (stringmatch(pattern,"masterauth",0)) {
        addReplyBulkCString(c,"masterauth");
        addReplyBulkCString(c,server.masterauth);
        matches++;
    }
    if (stringmatch(pattern,"maxmemory",0)) {
        char buf[128];

        ll2string(buf,128,server.maxmemory);
        addReplyBulkCString(c,"maxmemory");
        addReplyBulkCString(c,buf);
        matches++;
    }
    if (stringmatch(pattern,"timeout",0)) {
        char buf[128];

        ll2string(buf,128,server.maxidletime);
        addReplyBulkCString(c,"timeout");
        addReplyBulkCString(c,buf);
        matches++;
    }
    if (stringmatch(pattern,"appendonly",0)) {
        addReplyBulkCString(c,"appendonly");
        addReplyBulkCString(c,server.appendonly ? "yes" : "no");
        matches++;
    }
    if (stringmatch(pattern,"appendfsync",0)) {
        char *policy;

        switch(server.appendfsync) {
        case APPENDFSYNC_NO: policy = "no"; break;
        case APPENDFSYNC_EVERYSEC: policy = "everysec"; break;
        case APPENDFSYNC_ALWAYS: policy = "always"; break;
        default: policy = "unknown"; break; /* too harmless to panic */
        }
        addReplyBulkCString(c,"appendfsync");
        addReplyBulkCString(c,policy);
        matches++;
    }
    if (stringmatch(pattern,"save",0)) {
        sds buf = sdsempty();
        int j;

        for (j = 0; j < server.saveparamslen; j++) {
            buf = sdscatprintf(buf,"%ld %d",
                    server.saveparams[j].seconds,
                    server.saveparams[j].changes);
            if (j != server.saveparamslen-1)
                buf = sdscatlen(buf," ",1);
        }
        addReplyBulkCString(c,"save");
        addReplyBulkCString(c,buf);
        sdsfree(buf);
        matches++;
    }
    decrRefCount(o);
    lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",matches*2);
}
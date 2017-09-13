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

        snprintf(buf,128,"%llu\n",server.maxmemory);
        addReplyBulkCString(c,"maxmemory");
        addReplyBulkCString(c,buf);
        matches++;
    }
    decrRefCount(o);
    lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",matches*2);
}
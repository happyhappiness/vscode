static void debugCommand(redisClient *c) {
    if (!strcasecmp(c->argv[1]->ptr,"segfault")) {
        *((char*)-1) = 'x';
    } else if (!strcasecmp(c->argv[1]->ptr,"object") && c->argc == 3) {
        dictEntry *de = dictFind(c->db->dict,c->argv[2]);
        robj *key, *val;

        if (!de) {
            addReply(c,shared.nokeyerr);
            return;
        }
        key = dictGetEntryKey(de);
        val = dictGetEntryVal(de);
        addReplySds(c,sdscatprintf(sdsempty(),
            "+Key at:%p refcount:%d, value at:%p refcount:%d\r\n",
                key, key->refcount, val, val->refcount));
    } else {
        addReplySds(c,sdsnew(
            "-ERR Syntax error, try DEBUG [SEGFAULT|OBJECT <key>]\r\n"));
    }
}


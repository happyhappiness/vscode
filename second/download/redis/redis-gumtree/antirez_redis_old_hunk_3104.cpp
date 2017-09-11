void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
    listNode *ln;
    listIter li;
    int outc = 0, j;
    robj **outv;
    /* We need 1+(ARGS*3) objects since commands are using the new protocol
     * and we one 1 object for the first "*<count>\r\n" multibulk count, then
     * for every additional object we have "$<count>\r\n" + object + "\r\n". */
    robj *static_outv[REDIS_STATIC_ARGS*3+1];
    robj *lenobj;

    if (argc <= REDIS_STATIC_ARGS) {
        outv = static_outv;
    } else {
        outv = zmalloc(sizeof(robj*)*(argc*3+1));
    }

    lenobj = createObject(REDIS_STRING,
            sdscatprintf(sdsempty(), "*%d\r\n", argc));
    lenobj->refcount = 0;
    outv[outc++] = lenobj;
    for (j = 0; j < argc; j++) {
        lenobj = createObject(REDIS_STRING,
            sdscatprintf(sdsempty(),"$%lu\r\n",
                (unsigned long) stringObjectLen(argv[j])));
        lenobj->refcount = 0;
        outv[outc++] = lenobj;
        outv[outc++] = argv[j];
        outv[outc++] = shared.crlf;
    }

    /* Increment all the refcounts at start and decrement at end in order to
     * be sure to free objects if there is no slave in a replication state
     * able to be feed with commands */
    for (j = 0; j < outc; j++) incrRefCount(outv[j]);
    listRewind(slaves,&li);
    while((ln = listNext(&li))) {
        redisClient *slave = ln->value;

        /* Don't feed slaves that are still waiting for BGSAVE to start */
        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) continue;

        /* Feed all the other slaves, MONITORs and so on */
        if (slave->slaveseldb != dictid) {
            robj *selectcmd;


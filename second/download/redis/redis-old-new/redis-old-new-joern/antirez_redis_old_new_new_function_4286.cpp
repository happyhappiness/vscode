static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int dictid, robj **argv, int argc) {
    listNode *ln;
    int outc = 0, j;
    robj **outv;
    /* (args*2)+1 is enough room for args, spaces, newlines */
    robj *static_outv[REDIS_STATIC_ARGS*2+1];

    if (argc <= REDIS_STATIC_ARGS) {
        outv = static_outv;
    } else {
        outv = zmalloc(sizeof(robj*)*(argc*2+1));
    }
    
    for (j = 0; j < argc; j++) {
        if (j != 0) outv[outc++] = shared.space;
        if ((cmd->flags & REDIS_CMD_BULK) && j == argc-1) {
            robj *lenobj;

            lenobj = createObject(REDIS_STRING,
                sdscatprintf(sdsempty(),"%lu\r\n",
                    stringObjectLen(argv[j])));
            lenobj->refcount = 0;
            outv[outc++] = lenobj;
        }
        outv[outc++] = argv[j];
    }
    outv[outc++] = shared.crlf;

    /* Increment all the refcounts at start and decrement at end in order to
     * be sure to free objects if there is no slave in a replication state
     * able to be feed with commands */
    for (j = 0; j < outc; j++) incrRefCount(outv[j]);
    listRewind(slaves);
    while((ln = listYield(slaves))) {
        redisClient *slave = ln->value;

        /* Don't feed slaves that are still waiting for BGSAVE to start */
        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) continue;

        /* Feed all the other slaves, MONITORs and so on */
        if (slave->slaveseldb != dictid) {
            robj *selectcmd;

            switch(dictid) {
            case 0: selectcmd = shared.select0; break;
            case 1: selectcmd = shared.select1; break;
            case 2: selectcmd = shared.select2; break;
            case 3: selectcmd = shared.select3; break;
            case 4: selectcmd = shared.select4; break;
            case 5: selectcmd = shared.select5; break;
            case 6: selectcmd = shared.select6; break;
            case 7: selectcmd = shared.select7; break;
            case 8: selectcmd = shared.select8; break;
            case 9: selectcmd = shared.select9; break;
            default:
                selectcmd = createObject(REDIS_STRING,
                    sdscatprintf(sdsempty(),"select %d\r\n",dictid));
                selectcmd->refcount = 0;
                break;
            }
            addReply(slave,selectcmd);
            slave->slaveseldb = dictid;
        }
        for (j = 0; j < outc; j++) addReply(slave,outv[j]);
    }
    for (j = 0; j < outc; j++) decrRefCount(outv[j]);
    if (outv != static_outv) zfree(outv);
}
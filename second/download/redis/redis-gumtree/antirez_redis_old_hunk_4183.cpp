
/* ============================= Hash commands ============================== */
static void hsetCommand(redisClient *c) {
    int update = 0;
    robj *o;

    if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
    hashTryConversion(o,c->argv,2,3);
    update = hashReplace(o,c->argv[2],c->argv[3]);
    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",update == 0));
    server.dirty++;
}


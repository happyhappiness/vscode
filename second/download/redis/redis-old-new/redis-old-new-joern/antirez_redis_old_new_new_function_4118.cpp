static void hsetCommand(redisClient *c) {
    int update;
    robj *o;

    if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
    hashTryConversion(o,c->argv,2,3);
    update = hashReplace(o,c->argv[2],c->argv[3]);
    addReply(c, update ? shared.czero : shared.cone);
    server.dirty++;
}
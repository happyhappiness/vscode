void hincrbyfloatCommand(redisClient *c) {
    double long value, incr;
    robj *o, *current, *new, *aux;

    if (getLongDoubleFromObjectOrReply(c,c->argv[3],&incr,NULL) != REDIS_OK) return;
    if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
    if ((current = hashTypeGetObject(o,c->argv[2])) != NULL) {
        if (getLongDoubleFromObjectOrReply(c,current,&value,
            "hash value is not a valid float") != REDIS_OK) {
            decrRefCount(current);
            return;
        }
        decrRefCount(current);
    } else {
        value = 0;
    }

    value += incr;
    new = createStringObjectFromLongDouble(value);
    hashTypeTryObjectEncoding(o,&c->argv[2],NULL);
    hashTypeSet(o,c->argv[2],new);
    addReplyBulk(c,new);
    signalModifiedKey(c->db,c->argv[1]);
    notifyKeyspaceEvent("hincrbyfloat",c->argv[1],c->db->id);
    server.dirty++;

    /* Always replicate HINCRBYFLOAT as an HSET command with the final value
     * in order to make sure that differences in float pricision or formatting
     * will not create differences in replicas or after an AOF restart. */
    aux = createStringObject("HSET",4);
    rewriteClientCommandArgument(c,0,aux);
    decrRefCount(aux);
    rewriteClientCommandArgument(c,3,new);
    decrRefCount(new);
}
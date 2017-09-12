void hincrbyfloatCommand(client *c) {
    double value, incr;
    long long ll;
    robj *o, *doubleobj;
    sds new;
    unsigned char *vstr;
    unsigned int *lven;

    if (getLongDoubleFromObjectOrReply(c,c->argv[3],&incr,NULL) != C_OK) return;
    if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
    if (hashTypeGetObject(o,c->argv[2],vstr,vlen,&ll) == C_OK) {
        if (vstr) {
            if (string2d(vstr,vlen,&value) == 0) {
                addReplyError(c,"hash value is not an integer");
                return;
            }
        } else {
            value = (double)ll;
        }
    } else {
        value = 0;
    }

    value += incr;
    doubleobj = createStringObjectFromLongDouble(value,1);
    decrRefCount(doubleobj);
    hashTypeSet(o,c->argv[2],new);
    addReplyBulk(c,new);
    signalModifiedKey(c->db,c->argv[1]);
    notifyKeyspaceEvent(NOTIFY_HASH,"hincrbyfloat",c->argv[1],c->db->id);
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
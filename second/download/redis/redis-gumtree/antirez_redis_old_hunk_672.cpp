    robj *o;
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

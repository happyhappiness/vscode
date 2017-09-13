static void hsetCommand(redisClient *c) {
    int update = 0;
    robj *o = lookupKeyWrite(c->db,c->argv[1]);

    if (o == NULL) {
        o = createHashObject();
        dictAdd(c->db->dict,c->argv[1],o);
        incrRefCount(c->argv[1]);
    } else {
        if (o->type != REDIS_HASH) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
    }
    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        unsigned char *zm = o->ptr;

        zm = zipmapSet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr),
            c->argv[3]->ptr,sdslen(c->argv[3]->ptr),&update);
    } else {
        if (dictAdd(o->ptr,c->argv[2],c->argv[3]) == DICT_OK) {
            incrRefCount(c->argv[2]);
        } else {
            update = 1;
        }
        incrRefCount(c->argv[3]);
    }
    server.dirty++;
    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",update == 0));
}
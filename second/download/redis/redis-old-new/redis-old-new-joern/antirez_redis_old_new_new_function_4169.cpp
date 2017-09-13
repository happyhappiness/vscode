static void llenCommand(redisClient *c) {
    robj *o;
    list *l;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_LIST)) return;
    
    l = o->ptr;
    addReplyUlong(c,listLength(l));
}
static void decrRefCount(void *obj) {
    robj *o = obj;

#ifdef DEBUG_REFCOUNT
    if (o->type == REDIS_STRING)
        printf("Decrement '%s'(%p), now is: %d\n",o->ptr,o,o->refcount-1);
#endif
    if (--(o->refcount) == 0) {
        switch(o->type) {
        case REDIS_STRING: freeStringObject(o); break;
        case REDIS_LIST: freeListObject(o); break;
        case REDIS_SET: freeSetObject(o); break;
        case REDIS_HASH: freeHashObject(o); break;
        default: assert(0 != 0); break;
        }
        if (listLength(server.objfreelist) > REDIS_OBJFREELIST_MAX ||
            !listAddNodeHead(server.objfreelist,o))
            zfree(o);
    }
}
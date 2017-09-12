}

static void incrRefCount(robj *o) {
    o->refcount++;
#ifdef DEBUG_REFCOUNT
    if (o->type == REDIS_STRING)
        printf("Increment '%s'(%p), now is: %d\n",o->ptr,o,o->refcount);
#endif
}

static void decrRefCount(void *obj) {
    robj *o = obj;

#ifdef DEBUG_REFCOUNT
    if (o->type == REDIS_STRING)
        printf("Decrement '%s'(%p), now is: %d\n",o->ptr,o,o->refcount-1);
#endif
    if (--(o->refcount) == 0) {
        switch(o->type) {
        case REDIS_STRING: freeStringObject(o); break;

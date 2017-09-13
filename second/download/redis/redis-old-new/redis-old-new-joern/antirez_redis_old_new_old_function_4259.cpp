static void incrRefCount(robj *o) {
    o->refcount++;
#ifdef DEBUG_REFCOUNT
    if (o->type == REDIS_STRING)
        printf("Increment '%s'(%p), now is: %d\n",o->ptr,o,o->refcount);
#endif
}
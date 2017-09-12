
static void incrRefCount(robj *o) {
    o->refcount++;
}

static void decrRefCount(void *obj) {
    robj *o = obj;
    if (--(o->refcount) == 0) {
        switch(o->type) {
        case REDIS_STRING: freeStringObject(o); break;

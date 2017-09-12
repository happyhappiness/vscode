}

static void incrRefCount(robj *o) {
    assert(!server.vm_enabled || o->storage == REDIS_VM_MEMORY);
    o->refcount++;
}

static void decrRefCount(void *obj) {
    robj *o = obj;

    /* REDIS_VM_SWAPPED */
    if (server.vm_enabled && o->storage == REDIS_VM_SWAPPED) {
        assert(o->refcount == 1);
        assert(o->type == REDIS_STRING);
        freeStringObject(o);
        vmMarkPagesFree(o->vm.page,o->vm.usedpages);
        if (listLength(server.objfreelist) > REDIS_OBJFREELIST_MAX ||
            !listAddNodeHead(server.objfreelist,o))
            zfree(o);
        return;
    }
    /* REDIS_VM_MEMORY */
    if (--(o->refcount) == 0) {
        switch(o->type) {
        case REDIS_STRING: freeStringObject(o); break;

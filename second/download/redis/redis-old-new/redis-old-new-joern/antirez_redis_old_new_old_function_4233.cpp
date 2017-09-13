static int vmSwapObjectBlocking(robj *key, robj *val) {
    off_t pages = rdbSavedObjectPages(val,NULL);
    off_t page;

    assert(key->storage == REDIS_VM_MEMORY);
    assert(key->refcount == 1);
    if (vmFindContiguousPages(&page,pages) == REDIS_ERR) return REDIS_ERR;
    if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
        redisLog(REDIS_WARNING,
            "Critical VM problem in vmSwapObjectBlocking(): can't seek: %s",
            strerror(errno));
        return REDIS_ERR;
    }
    rdbSaveObject(server.vm_fp,val);
    key->vm.page = page;
    key->vm.usedpages = pages;
    key->storage = REDIS_VM_SWAPPED;
    key->vtype = val->type;
    decrRefCount(val); /* Deallocate the object from memory. */
    vmMarkPagesUsed(page,pages);
    redisLog(REDIS_DEBUG,"VM: object %s swapped out at %lld (%lld pages)",
        (unsigned char*) key->ptr,
        (unsigned long long) page, (unsigned long long) pages);
    server.vm_stats_swapped_objects++;
    server.vm_stats_swapouts++;
    fflush(server.vm_fp);
    return REDIS_OK;
}
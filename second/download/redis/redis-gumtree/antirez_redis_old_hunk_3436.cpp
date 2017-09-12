    if (aeCreateFileEvent(server.el, server.io_ready_pipe_read, AE_READABLE,
        vmThreadedIOCompletedJob, NULL) == AE_ERR)
        oom("creating file event");
}

/* Write the specified object at the specified page of the swap file */
int vmWriteObjectOnSwap(robj *o, off_t page) {
    if (server.vm_enabled) pthread_mutex_lock(&server.io_swapfile_mutex);
    if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
        if (server.vm_enabled) pthread_mutex_unlock(&server.io_swapfile_mutex);
        redisLog(REDIS_WARNING,
            "Critical VM problem in vmWriteObjectOnSwap(): can't seek: %s",
            strerror(errno));
        return REDIS_ERR;
    }
    rdbSaveObject(server.vm_fp,o);
    fflush(server.vm_fp);
    if (server.vm_enabled) pthread_mutex_unlock(&server.io_swapfile_mutex);
    return REDIS_OK;
}

/* Transfers the 'val' object to disk. Store all the information
 * a 'vmpointer' object containing all the information needed to load the
 * object back later is returned.
 *
 * If we can't find enough contiguous empty pages to swap the object on disk
 * NULL is returned. */
vmpointer *vmSwapObjectBlocking(robj *val) {
    off_t pages = rdbSavedObjectPages(val);
    off_t page;
    vmpointer *vp;

    redisAssert(val->storage == REDIS_VM_MEMORY);
    redisAssert(val->refcount == 1);
    if (vmFindContiguousPages(&page,pages) == REDIS_ERR) return NULL;
    if (vmWriteObjectOnSwap(val,page) == REDIS_ERR) return NULL;

    vp = createVmPointer(val->type);
    vp->page = page;
    vp->usedpages = pages;
    decrRefCount(val); /* Deallocate the object from memory. */
    vmMarkPagesUsed(page,pages);
    redisLog(REDIS_DEBUG,"VM: object %p swapped out at %lld (%lld pages)",
        (void*) val,
        (unsigned long long) page, (unsigned long long) pages);
    server.vm_stats_swapped_objects++;
    server.vm_stats_swapouts++;
    return vp;
}

robj *vmReadObjectFromSwap(off_t page, int type) {
    robj *o;

    if (server.vm_enabled) pthread_mutex_lock(&server.io_swapfile_mutex);
    if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
        redisLog(REDIS_WARNING,
            "Unrecoverable VM problem in vmReadObjectFromSwap(): can't seek: %s",
            strerror(errno));
        _exit(1);
    }
    o = rdbLoadObject(type,server.vm_fp);
    if (o == NULL) {
        redisLog(REDIS_WARNING, "Unrecoverable VM problem in vmReadObjectFromSwap(): can't load object from swap file: %s", strerror(errno));
        _exit(1);
    }
    if (server.vm_enabled) pthread_mutex_unlock(&server.io_swapfile_mutex);
    return o;
}

/* Load the specified object from swap to memory.
 * The newly allocated object is returned.
 *
 * If preview is true the unserialized object is returned to the caller but
 * the pages are not marked as freed, nor the vp object is freed. */
robj *vmGenericLoadObject(vmpointer *vp, int preview) {
    robj *val;

    redisAssert(vp->type == REDIS_VMPOINTER &&
        (vp->storage == REDIS_VM_SWAPPED || vp->storage == REDIS_VM_LOADING));
    val = vmReadObjectFromSwap(vp->page,vp->vtype);
    if (!preview) {
        redisLog(REDIS_DEBUG, "VM: object %p loaded from disk", (void*)vp);
        vmMarkPagesFree(vp->page,vp->usedpages);
        zfree(vp);
        server.vm_stats_swapped_objects--;
    } else {
        redisLog(REDIS_DEBUG, "VM: object %p previewed from disk", (void*)vp);
    }
    server.vm_stats_swapins++;
    return val;
}

/* Plain object loading, from swap to memory.
 *
 * 'o' is actually a redisVmPointer structure that will be freed by the call.
 * The return value is the loaded object. */
robj *vmLoadObject(robj *o) {
    /* If we are loading the object in background, stop it, we
     * need to load this object synchronously ASAP. */
    if (o->storage == REDIS_VM_LOADING)
        vmCancelThreadedIOJob(o);
    return vmGenericLoadObject((vmpointer*)o,0);
}

/* Just load the value on disk, without to modify the key.
 * This is useful when we want to perform some operation on the value
 * without to really bring it from swap to memory, like while saving the
 * dataset or rewriting the append only log. */
robj *vmPreviewObject(robj *o) {
    return vmGenericLoadObject((vmpointer*)o,1);
}

/* How a good candidate is this object for swapping?
 * The better candidate it is, the greater the returned value.
 *
 * Currently we try to perform a fast estimation of the object size in
 * memory, and combine it with aging informations.
 *
 * Basically swappability = idle-time * log(estimated size)
 *
 * Bigger objects are preferred over smaller objects, but not
 * proportionally, this is why we use the logarithm. This algorithm is
 * just a first try and will probably be tuned later. */
double computeObjectSwappability(robj *o) {
    /* actual age can be >= minage, but not < minage. As we use wrapping
     * 21 bit clocks with minutes resolution for the LRU. */
    return (double) estimateObjectIdleTime(o);
}

/* Try to swap an object that's a good candidate for swapping.
 * Returns REDIS_OK if the object was swapped, REDIS_ERR if it's not possible
 * to swap any object at all.
 *
 * If 'usethreaded' is true, Redis will try to swap the object in background
 * using I/O threads. */
int vmSwapOneObject(int usethreads) {
    int j, i;
    struct dictEntry *best = NULL;
    double best_swappability = 0;

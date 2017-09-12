            offset++;
        }
    }
    return REDIS_ERR;
}

/* Swap the 'val' object relative to 'key' into disk. Store all the information
 * needed to later retrieve the object into the key object.
 * If we can't find enough contiguous empty pages to swap the object on disk
 * REDIS_ERR is returned. */
static int vmSwapObject(robj *key, robj *val) {
    off_t pages = rdbSavedObjectPages(val);
    off_t page;

    assert(key->storage == REDIS_VM_MEMORY);
    if (vmFindContiguousPages(&page,pages) == REDIS_ERR) return REDIS_ERR;
    if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
        redisLog(REDIS_WARNING,
            "Critical VM problem in vmSwapObject(): can't seek: %s",
            strerror(errno));
        return REDIS_ERR;
    }
    rdbSaveObject(server.vm_fp,val);
    key->vm.page = page;
    key->vm.usedpages = pages;
    key->storage = REDIS_VM_SWAPPED;
    decrRefCount(val); /* Deallocate the object from memory. */
    vmMarkPagesUsed(page,pages);
    return REDIS_OK;
}

/* Load the value object relative to the 'key' object from swap to memory.
 * The newly allocated object is returned. */
static robj *vmLoadObject(robj *key) {
    robj *val;

    assert(key->storage == REDIS_VM_SWAPPED);
    if (fseeko(server.vm_fp,key->vm.page*server.vm_page_size,SEEK_SET) == -1) {
        redisLog(REDIS_WARNING,
            "Unrecoverable VM problem in vmLoadObject(): can't seek: %s",
            strerror(errno));
        exit(1);
    }
    val = rdbLoadObject(key->type,server.vm_fp);
    if (val == NULL) {
        redisLog(REDIS_WARNING, "Unrecoverable VM problem in vmLoadObject(): can't load object from swap file: %s", strerror(errno));
        exit(1);
    }
    key->storage = REDIS_VM_MEMORY;
    key->vm.atime = server.unixtime;
    vmMarkPagesFree(key->vm.page,key->vm.usedpages);
    return val;
}

/* ================================= Debugging ============================== */

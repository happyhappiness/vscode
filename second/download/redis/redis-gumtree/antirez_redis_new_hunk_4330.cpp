        redisLog(REDIS_WARNING, "Unrecoverable VM problem in vmLoadObject(): can't load object from swap file: %s", strerror(errno));
        exit(1);
    }
    if (!preview) {
        key->storage = REDIS_VM_MEMORY;
        key->vm.atime = server.unixtime;
        vmMarkPagesFree(key->vm.page,key->vm.usedpages);
        redisLog(REDIS_DEBUG, "VM: object %s loaded from disk",
            (unsigned char*) key->ptr);
    }
    return val;
}

/* Plain object loading, from swap to memory */
static robj *vmLoadObject(robj *key) {
    return vmGenericLoadObject(key,0);
}

/* Just load the value on disk, without to modify the key.
 * This is useful when we want to perform some operation on the value
 * without to really bring it from swap to memory, like while saving the
 * dataset or rewriting the append only log. */
static robj *vmPreviewObject(robj *key) {
    return vmGenericLoadObject(key,1);
}

/* How a good candidate is this object for swapping?
 * The better candidate it is, the greater the returned value.
 *

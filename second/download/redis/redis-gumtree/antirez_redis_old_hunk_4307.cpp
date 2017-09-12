    return REDIS_OK;
}

/* Load the value object relative to the 'key' object from swap to memory.
 * The newly allocated object is returned.
 *
 * If preview is true the unserialized object is returned to the caller but
 * no changes are made to the key object, nor the pages are marked as freed */
static robj *vmGenericLoadObject(robj *key, int preview) {
    robj *val;

    redisAssert(key->storage == REDIS_VM_SWAPPED);
    if (fseeko(server.vm_fp,key->vm.page*server.vm_page_size,SEEK_SET) == -1) {
        redisLog(REDIS_WARNING,
            "Unrecoverable VM problem in vmLoadObject(): can't seek: %s",
            strerror(errno));
        exit(1);
    }
    val = rdbLoadObject(key->vtype,server.vm_fp);
    if (val == NULL) {
        redisLog(REDIS_WARNING, "Unrecoverable VM problem in vmLoadObject(): can't load object from swap file: %s", strerror(errno));
        exit(1);
    }
    if (!preview) {
        key->storage = REDIS_VM_MEMORY;
        key->vm.atime = server.unixtime;

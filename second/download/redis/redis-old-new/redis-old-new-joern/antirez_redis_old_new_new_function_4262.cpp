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
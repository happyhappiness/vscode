        redisLog(REDIS_WARNING, "Unrecoverable VM problem in vmLoadObject(): can't load object from swap file: %s", strerror(errno));
        exit(1);
    }
    key->storage = REDIS_VM_MEMORY;
    key->vm.atime = server.unixtime;
    vmMarkPagesFree(key->vm.page,key->vm.usedpages);
    redisLog(REDIS_DEBUG, "VM: object %s loaded from disk",
        (unsigned char*) key->ptr);
    return val;
}

/* How a good candidate is this object for swapping?
 * The better candidate it is, the greater the returned value.
 *

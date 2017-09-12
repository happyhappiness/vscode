            strerror(errno));
        exit(1);
    }
    val = rdbLoadObject(key->vtype,server.vm_fp);
    if (val == NULL) {
        redisLog(REDIS_WARNING, "Unrecoverable VM problem in vmLoadObject(): can't load object from swap file: %s", strerror(errno));
        exit(1);

         */
        if (!r->filename) {
            return DECLINED;
        }
    }

    /* Allocate and initialize cache_object_t */
    obj = calloc(1, sizeof(*obj));
    if (!obj) {
        return DECLINED;
    }
    key_len = strlen(key) + 1;
    obj->key = malloc(key_len);
    if (!obj->key) {
        cleanup_cache_object(obj);
        return DECLINED;
    }
    memcpy((void*)obj->key, key, key_len);

    /* Allocate and init mem_cache_object_t */
    mobj = calloc(1, sizeof(*mobj));
    if (!mobj) {
        cleanup_cache_object(obj);
        return DECLINED;
    }

    /* Finish initing the cache object */
    apr_atomic_set32(&obj->refcount, 1);
    mobj->total_refs = 1;
    obj->complete = 0;
    obj->vobj = mobj;

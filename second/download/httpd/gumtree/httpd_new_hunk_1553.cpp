         */
        if (!r->filename) {
            return DECLINED;
        }
    }

    rv = apr_pool_create(&pool, NULL);

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
                     "mem_cache: Failed to create memory pool.");
        return DECLINED;
    }

    /* Allocate and initialize cache_object_t */
    obj = apr_pcalloc(pool, sizeof(*obj));
    obj->key = apr_pstrdup(pool, key);

    /* Allocate and init mem_cache_object_t */
    mobj = apr_pcalloc(pool, sizeof(*mobj));
    mobj->pool = pool;

    /* Finish initing the cache object */
    apr_atomic_set32(&obj->refcount, 1);
    mobj->total_refs = 1;
    obj->complete = 0;
    obj->vobj = mobj;

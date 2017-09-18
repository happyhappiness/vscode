    cache->handle = apr_palloc(r->pool, sizeof(cache_handle_t));

    while (next) {
        type = ap_cache_tokstr(r->pool, next, &next);
        switch ((rv = cache_run_open_entity(cache->handle, r, type, key))) {
        case OK: {
            info = &(cache->handle->cache_obj->info);
            /* XXX:
             * Handle being returned a collection of entities.
             */

            /* Has the cache entry expired? */
            if (r->request_time > info->expire)
                cache->fresh = 0;
            else
                cache->fresh = 1;

            /*** do content negotiation here */
            return OK;
        }
        case DECLINED: {
            /* try again with next cache type */
            continue;
        }

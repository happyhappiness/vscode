apr_status_t cache_remove_lock(cache_server_conf *conf,
        cache_request_rec *cache, request_rec *r, apr_bucket_brigade *bb)
{
    void *dummy;
    const char *lockname;

    if (!conf || !conf->lock || !conf->lockpath) {
        /* no locks configured, leave */
        return APR_SUCCESS;
    }
    if (bb) {
        apr_bucket *e;
        int eos_found = 0;
        for (e = APR_BRIGADE_FIRST(bb);
             e != APR_BRIGADE_SENTINEL(bb);
             e = APR_BUCKET_NEXT(e))
        {
            if (APR_BUCKET_IS_EOS(e)) {
                eos_found = 1;
                break;
            }
        }
        if (!eos_found) {
            /* no eos found in brigade, don't delete anything just yet,
             * we are not done.
             */
            return APR_SUCCESS;
        }
    }
    apr_pool_userdata_get(&dummy, CACHE_LOCKFILE_KEY, r->pool);
    if (dummy) {
        return apr_file_close((apr_file_t *)dummy);
    }
    apr_pool_userdata_get(&dummy, CACHE_LOCKNAME_KEY, r->pool);
    lockname = (const char *)dummy;
    if (!lockname) {
        char dir[5];

        /* create the key if it doesn't exist */
        if (!cache->key) {
            cache_generate_key(r, r->pool, &cache->key);
        }

        /* create a hashed filename from the key, and save it for later */
        lockname = ap_cache_generate_name(r->pool, 0, 0, cache->key);

        /* lock files represent discrete just-went-stale URLs "in flight", so
         * we support a simple two level directory structure, more is overkill.
         */
        dir[0] = '/';
        dir[1] = lockname[0];
        dir[2] = '/';
        dir[3] = lockname[1];
        dir[4] = 0;

        lockname = apr_pstrcat(r->pool, conf->lockpath, dir, "/", lockname, NULL);
    }
    return apr_file_remove(lockname, r->pool);
}
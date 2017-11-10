int cstat (NXPathCtx_t ctx, char *path, struct stat *buf, unsigned long requestmap, apr_pool_t *p)
{
    apr_pool_t *gPool = (apr_pool_t *)getGlobalPool();
    apr_hash_t *statCache = NULL;
    apr_thread_rwlock_t *rwlock = NULL;

    NXPathCtx_t pathctx = 0;
    char *ptr = NULL, *tr;
    int len = 0, x;
    char *ppath;
    char *pinfo;

    if (ctx == 1) {

        /* If there isn't a global pool then just stat the file
           and return */
        if (!gPool) {
            char poolname[50];
    
            if (apr_pool_create(&gPool, NULL) != APR_SUCCESS) {
                return getstat(ctx, path, buf, requestmap);
            }
    
            setGlobalPool(gPool);
            apr_pool_tag(gPool, apr_pstrdup(gPool, "cstat_mem_pool"));
    
            statCache = apr_hash_make(gPool);
            apr_pool_userdata_set ((void*)statCache, "STAT_CACHE", stat_cache_cleanup, gPool);

            apr_thread_rwlock_create(&rwlock, gPool);
            apr_pool_userdata_set ((void*)rwlock, "STAT_CACHE_LOCK", apr_pool_cleanup_null, gPool);
        }
        else {
            apr_pool_userdata_get((void**)&statCache, "STAT_CACHE", gPool);
            apr_pool_userdata_get((void**)&rwlock, "STAT_CACHE_LOCK", gPool);
        }

        if (!gPool || !statCache || !rwlock) {
            return getstat(ctx, path, buf, requestmap);
        }
    
        for (x = 0,tr = path;*tr != '\0';tr++,x++) {
            if (*tr == '\\' || *tr == '/') {
                ptr = tr;
                len = x;
            }
            if (*tr == ':') {
                ptr = "\\";
                len = x;
            }
        }
    
        if (ptr) {
            ppath = apr_pstrndup (p, path, len);
            strlwr(ppath);
            if (ptr[1] != '\0') {
                ptr++;
            }
            /* If the path ended in a trailing slash then our result path
               will be a single slash. To avoid stat'ing the root with a
               slash, we need to make sure we stat the current directory
               with a dot */
            if (((*ptr == '/') || (*ptr == '\\')) && (*(ptr+1) == '\0')) {
                pinfo = apr_pstrdup (p, ".");
            }
            else {
                pinfo = apr_pstrdup (p, ptr);
            }
        }
    
        /* If we have a statCache then try to pull the information
           from the cache.  Otherwise just stat the file and return.*/
        if (statCache) {
            apr_thread_rwlock_rdlock(rwlock);
            pathctx = (NXPathCtx_t) apr_hash_get(statCache, ppath, APR_HASH_KEY_STRING);
            apr_thread_rwlock_unlock(rwlock);
            if (pathctx) {
                return getstat(pathctx, pinfo, buf, requestmap);
            }
            else {
                int err;

                err = NXCreatePathContext(0, ppath, 0, NULL, &pathctx);
                if (!err) {
                    apr_thread_rwlock_wrlock(rwlock);
                    apr_hash_set(statCache, apr_pstrdup(gPool,ppath) , APR_HASH_KEY_STRING, (void*)pathctx);
                    apr_thread_rwlock_unlock(rwlock);
                    return getstat(pathctx, pinfo, buf, requestmap);
                }
            }
        }
    }
    return getstat(ctx, path, buf, requestmap);
}
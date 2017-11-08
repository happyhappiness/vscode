int cstat (const char *path, struct stat *buf, char **casedName, apr_pool_t *pool)
{
    apr_hash_t *statCache = (apr_hash_t *)getStatCache(CpuCurrentProcessor);
    apr_pool_t *gPool = (apr_pool_t *)getGlobalPool(CpuCurrentProcessor);
    apr_stat_entry_t *stat_entry;
    struct stat *info;
    apr_time_t now = apr_time_now();
    char *key;
    int ret;
    int found = 0;

    *casedName = NULL;

    /* If there isn't a global pool then just stat the file
       and return */
    if (!gPool) {
        char poolname[50];

        if (apr_pool_create(&gPool, NULL) != APR_SUCCESS) {
            ret = stat(path, buf);
            if (ret == 0)
                *casedName = case_filename(pool, path);
            return ret;
        }

        sprintf (poolname, "cstat_mem_pool_%d", CpuCurrentProcessor);
        apr_pool_tag(gPool, poolname);

        setGlobalPool(gPool, CpuCurrentProcessor);
    }

    /* If we have a statCache hash table then use it.
       Otherwise we need to create it and initialized it
       with a new mutex lock. */
    if (!statCache) {
        statCache = apr_hash_make(gPool);
        setStatCache((void*)statCache, CpuCurrentProcessor);
    }

    /* If we have a statCache then try to pull the information
       from the cache.  Otherwise just stat the file and return.*/
    if (statCache) {
        stat_entry = (apr_stat_entry_t*) apr_hash_get(statCache, path, APR_HASH_KEY_STRING);
        /* If we got an entry then check the expiration time.  If the entry
           hasn't expired yet then copy the information and return. */
        if (stat_entry) {
            if ((now - stat_entry->expire) <= APR_USEC_PER_SEC) {
                memcpy (buf, &(stat_entry->info), sizeof(struct stat));
                if (stat_entry->casedName)
                    *casedName = apr_pstrdup (pool, stat_entry->casedName);
                else
                    *casedName = case_filename(pool, path);
                found = 1;
            }
        }

        /* Since we are creating a separate stat cache for each processor, we
           don't need to worry about locking the hash table before manipulating
           it. */
        if (!found) {
            /* Bind the thread to the current cpu so that we don't wake
               up on some other cpu and try to manipulate the wrong cache. */
            NXThreadBind (CpuCurrentProcessor);
            ret = stat(path, buf);
            if (ret == 0) {
                *casedName = case_filename(pool, path);
                /* If we don't have a stat_entry then create one, copy
                   the data and add it to the hash table. */
                if (!stat_entry) {
                    key = apr_pstrdup (gPool, path);
                    stat_entry = apr_palloc (gPool, sizeof(apr_stat_entry_t));
                    memcpy (&(stat_entry->info), buf, sizeof(struct stat));
                    if (*casedName)
                        stat_entry->casedName = apr_pstrdup (gPool, *casedName);
                    stat_entry->expire = now;
                    apr_hash_set(statCache, key, APR_HASH_KEY_STRING, stat_entry);
                }
                else {
                    /* If we do have a stat_entry then it must have expired.  Just
                       copy the data and reset the expiration. */
                    memcpy (&(stat_entry->info), buf, sizeof(struct stat));

                    /* If we have a casedName and don't have a cached name or the names don't
                       compare, then cache the name. */
                    if (*casedName && (!stat_entry->casedName || strcmp(*casedName, stat_entry->casedName))) {
                        stat_entry->casedName = apr_pstrdup (gPool, *casedName);
                    }
                    stat_entry->expire = now;
                }
                NXThreadBind (NX_THR_UNBOUND);
            }
            else{
                NXThreadBind (NX_THR_UNBOUND);
                return ret;
			}
        }
    }
    else {
        ret = stat(path, buf);
        if (ret == 0)
            *casedName = case_filename(pool, path);
        return ret;
    }
    return 0;
}
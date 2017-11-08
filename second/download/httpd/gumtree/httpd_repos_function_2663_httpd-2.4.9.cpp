apr_status_t isapi_lookup(apr_pool_t *p, server_rec *s, request_rec *r,
                          const char *fpath, isapi_loaded** isa)
{
    apr_status_t rv;
    const char *key;

    if ((rv = apr_thread_mutex_lock(loaded.lock)) != APR_SUCCESS) {
        return rv;
    }

    *isa = apr_hash_get(loaded.hash, fpath, APR_HASH_KEY_STRING);

    if (*isa) {

        /* If we find this lock exists, use a set-aside copy of gainlock
         * to avoid race conditions on NULLing the in_progress variable
         * when the load has completed.  Release the global isapi hash
         * lock so other requests can proceed, then rdlock for completion
         * of loading our desired dll or wrlock if we would like to retry
         * loading the dll (because last_load_rv failed and retry is up.)
         */
        apr_thread_rwlock_t *gainlock = (*isa)->in_progress;

        /* gainlock is NULLed after the module loads successfully.
         * This free-threaded module can be used without any locking.
         */
        if (!gainlock) {
            rv = (*isa)->last_load_rv;
            apr_thread_mutex_unlock(loaded.lock);
            return rv;
        }


        if ((*isa)->last_load_rv == APR_SUCCESS) {
            apr_thread_mutex_unlock(loaded.lock);
            if ((rv = apr_thread_rwlock_rdlock(gainlock))
                    != APR_SUCCESS) {
                return rv;
            }
            rv = (*isa)->last_load_rv;
            apr_thread_rwlock_unlock(gainlock);
            return rv;
        }

        if (apr_time_now() > (*isa)->last_load_time + ISAPI_RETRY) {

            /* Remember last_load_time before releasing the global
             * hash lock to avoid colliding with another thread
             * that hit this exception at the same time as our
             * retry attempt, since we unlock the global mutex
             * before attempting a write lock for this module.
             */
            apr_time_t check_time = (*isa)->last_load_time;
            apr_thread_mutex_unlock(loaded.lock);

            if ((rv = apr_thread_rwlock_wrlock(gainlock))
                    != APR_SUCCESS) {
                return rv;
            }

            /* If last_load_time is unchanged, we still own this
             * retry, otherwise presume another thread provided
             * our retry (for good or ill).  Relock the global
             * hash for updating last_load_ vars, so their update
             * is always atomic to the global lock.
             */
            if (check_time == (*isa)->last_load_time) {

                rv = isapi_load(loaded.pool, s, *isa);

                apr_thread_mutex_lock(loaded.lock);
                (*isa)->last_load_rv = rv;
                (*isa)->last_load_time = apr_time_now();
                apr_thread_mutex_unlock(loaded.lock);
            }
            else {
                rv = (*isa)->last_load_rv;
            }
            apr_thread_rwlock_unlock(gainlock);

            return rv;
        }

        /* We haven't hit timeup on retry, let's grab the last_rv
         * within the hash mutex before unlocking.
         */
        rv = (*isa)->last_load_rv;
        apr_thread_mutex_unlock(loaded.lock);

        return rv;
    }

    /* If the module was not found, it's time to create a hash key entry
     * before releasing the hash lock to avoid multiple threads from
     * loading the same module.
     */
    key = apr_pstrdup(loaded.pool, fpath);
    *isa = apr_pcalloc(loaded.pool, sizeof(isapi_loaded));
    (*isa)->filename = key;
    if (r) {
        /* A mutex that exists only long enough to attempt to
         * load this isapi dll, the release this module to all
         * other takers that came along during the one-time
         * load process.  Short lifetime for this lock would
         * be great, however, using r->pool is nasty if those
         * blocked on the lock haven't all unlocked before we
         * attempt to destroy.  A nastier race condition than
         * I want to deal with at this moment...
         */
        apr_thread_rwlock_create(&(*isa
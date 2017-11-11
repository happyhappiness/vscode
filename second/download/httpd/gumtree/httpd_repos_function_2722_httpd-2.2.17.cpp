apr_status_t apu_dso_init(apr_pool_t *pool)
{
    apr_status_t ret = APR_SUCCESS;
    apr_pool_t *global;
    apr_pool_t *parent;

    if (apr_atomic_inc32(&initialised)) {
        apr_atomic_set32(&initialised, 1); /* prevent wrap-around */

        while (apr_atomic_read32(&in_init)) /* wait until we get fully inited */
            ;

        return APR_SUCCESS;
    }

    /* Top level pool scope, need process-scope lifetime */
    for (parent = global = pool; parent; parent = apr_pool_parent_get(global))
         global = parent;

    dsos = apr_hash_make(global);

#if APR_HAS_THREADS
    ret = apr_thread_mutex_create(&mutex, APR_THREAD_MUTEX_DEFAULT, global);
    /* This already registers a pool cleanup */
#endif

    apr_pool_cleanup_register(global, NULL, apu_dso_term,
                              apr_pool_cleanup_null);

    apr_atomic_dec32(&in_init);

    return ret;
}
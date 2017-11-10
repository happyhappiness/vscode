apr_status_t apu_dso_init(apr_pool_t *pool)
{
    apr_status_t ret = APR_SUCCESS;
#if APU_DSO_BUILD
    apr_pool_t *global;
    apr_pool_t *parent;

    if (dsos != NULL) {
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

#endif /* APU_DSO_BUILD */
    return ret;
}
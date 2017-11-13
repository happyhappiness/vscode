static apr_status_t dbd_setup_init(apr_pool_t *pool, server_rec *s)
{
    dbd_group_t *group;
    apr_status_t rv = APR_SUCCESS;

    for (group = group_list; group; group = group->next) {
        apr_status_t rv2;

        rv2 = apr_pool_create(&group->pool, pool);
        if (rv2 != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv2, s,
                         "DBD: Failed to create reslist cleanup memory pool");
            return rv2;
        }

#if APR_HAS_THREADS
        rv2 = dbd_setup(s, group);
        if (rv2 == APR_SUCCESS) {
            continue;
        }
        else if (rv == APR_SUCCESS) {
            rv = rv2;
        }

        /* we failed, so create a mutex so that subsequent competing callers
         * to ap_dbd_open can serialize themselves while they retry
         */
        rv2 = apr_thread_mutex_create(&group->mutex,
                                      APR_THREAD_MUTEX_DEFAULT, pool);
        if (rv2 != APR_SUCCESS) {
             ap_log_error(APLOG_MARK, APLOG_CRIT, rv2, s,
                          "DBD: Failed to create thread mutex");
             return rv2;
        }
#endif
    }

    return rv;
}
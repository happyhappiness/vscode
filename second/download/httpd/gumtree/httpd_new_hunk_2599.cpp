
    for (group = group_list; group; group = group->next) {
        apr_status_t rv2;

        rv2 = apr_pool_create(&group->pool, pool);
        if (rv2 != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv2, s, APLOGNO(00634)
                         "Failed to create reslist cleanup memory pool");
            return rv2;
        }

#if APR_HAS_THREADS
        rv2 = dbd_setup(s, group);
        if (rv2 == APR_SUCCESS) {

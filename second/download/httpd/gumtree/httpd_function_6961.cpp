void ap_lua_init_mutex(apr_pool_t *pool, server_rec *s) 
{
    apr_status_t rv;
    
    /* global IVM mutex */
    rv = apr_global_mutex_child_init(&lua_ivm_mutex,
                                     apr_global_mutex_lockfile(lua_ivm_mutex),
                                     pool);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(03016)
                     "mod_lua: Failed to reopen mutex lua-ivm-shm in child");
        exit(1); /* bah :( */
    }
    
    /* Server pool mutex */
#if APR_HAS_THREADS
    apr_thread_mutex_create(&ap_lua_mutex, APR_THREAD_MUTEX_DEFAULT, pool);
#endif
}
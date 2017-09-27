    util_ldap_state_t *st_vhost;

    util_ldap_state_t *st = (util_ldap_state_t *)
                            ap_get_module_config(s->module_config,
                                                 &ldap_module);

    void *data;
    const char *userdata_key = "util_ldap_init";
    apr_ldap_err_t *result_err = NULL;
    int rc;

    /* util_ldap_post_config() will be called twice. Don't bother
     * going through all of the initialization on the first call
     * because it will just be thrown away.*/
    apr_pool_userdata_get(&data, userdata_key, s->process->pool);
    if (!data) {
        apr_pool_userdata_set((const void *)1, userdata_key,
                               apr_pool_cleanup_null, s->process->pool);

#if APR_HAS_SHARED_MEMORY
        /* If the cache file already exists then delete it.  Otherwise we are
         * going to run into problems creating the shared memory. */
        if (st->cache_file) {
            char *lck_file = apr_pstrcat(ptemp, st->cache_file, ".lck",
                                         NULL);
            apr_file_remove(lck_file, ptemp);
        }
#endif
        return OK;
    }

#if APR_HAS_SHARED_MEMORY
    /* initializing cache if shared memory size is not zero and we already
     * don't have shm address
     */
    if (!st->cache_shm && st->cache_bytes > 0) {
#endif
        result = util_ldap_cache_init(p, st);
        if (result != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, result, s,
                         "LDAP cache: could not create shared memory segment");
            return DONE;
        }

        result = ap_global_mutex_create(&st->util_ldap_cache_lock, NULL,
                                        ldap_cache_mutex_type, NULL, s, p, 0);

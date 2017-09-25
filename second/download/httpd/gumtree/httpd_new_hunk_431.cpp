
    return st;
}

static apr_status_t util_ldap_cleanup_module(void *data)
{
#if APR_HAS_LDAP_SSL && APR_HAS_NOVELL_LDAPSDK
    server_rec *s = data;
    util_ldap_state_t *st = (util_ldap_state_t *)ap_get_module_config(
        s->module_config, &ldap_module);
    
    if (st->ssl_support)
        ldapssl_client_deinit();

#endif
    return APR_SUCCESS;
}

static int util_ldap_post_config(apr_pool_t *p, apr_pool_t *plog, 
                                 apr_pool_t *ptemp, server_rec *s)
{
    int rc = LDAP_SUCCESS;
    apr_status_t result;
    char buf[MAX_STRING_LEN];
    server_rec *s_vhost;
    util_ldap_state_t *st_vhost;

    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(s->module_config, &ldap_module);

    void *data;
    const char *userdata_key = "util_ldap_init";

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
            char *lck_file = apr_pstrcat (st->pool, st->cache_file, ".lck", NULL);
            apr_file_remove(st->cache_file, ptemp);
            apr_file_remove(lck_file, ptemp);
        }
#endif
        return OK;
    }

#if APR_HAS_SHARED_MEMORY
    /* initializing cache if shared memory size is not zero and we already don't have shm address */
    if (!st->cache_shm && st->cache_bytes > 0) {
#endif
        result = util_ldap_cache_init(p, st);
        if (result != APR_SUCCESS) {
            apr_strerror(result, buf, sizeof(buf));
            ap_log_error(APLOG_MARK, APLOG_ERR, result, s,
                         "LDAP cache: error while creating a shared memory segment: %s", buf);
        }


#if APR_HAS_SHARED_MEMORY
        if (st->cache_file) {
            st->lock_file = apr_pstrcat (st->pool, st->cache_file, ".lck", NULL);
        }
        else
#endif
            st->lock_file = ap_server_root_relative(st->pool, tmpnam(NULL));

        result = apr_global_mutex_create(&st->util_ldap_cache_lock, st->lock_file, APR_LOCK_DEFAULT, st->pool);
        if (result != APR_SUCCESS) {
            return result;
        }

        /* merge config in all vhost */
        s_vhost = s->next;
        while (s_vhost) {
            st_vhost = (util_ldap_state_t *)ap_get_module_config(s_vhost->module_config, &ldap_module);

#if APR_HAS_SHARED_MEMORY
            st_vhost->cache_shm = st->cache_shm;
            st_vhost->cache_rmm = st->cache_rmm;
            st_vhost->cache_file = st->cache_file;
            ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, result, s, 
                         "LDAP merging Shared Cache conf: shm=0x%pp rmm=0x%pp for VHOST: %s",
                         st->cache_shm, st->cache_rmm, s_vhost->server_hostname);
#endif
            st_vhost->lock_file = st->lock_file;
            s_vhost = s_vhost->next;
        }
#if APR_HAS_SHARED_MEMORY
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "LDAP cache: LDAPSharedCacheSize is zero, disabling shared memory cache");
    }
#endif
    
    /* log the LDAP SDK used 
     */
    #if APR_HAS_NETSCAPE_LDAPSDK 

         * Add the new connection entry to the linked list. Note that we
         * don't actually establish an LDAP connection yet; that happens
         * the first time authentication is requested.
         */
        /* create the details to the pool in st */
        l = apr_pcalloc(st->pool, sizeof(util_ldap_connection_t));
        if (apr_pool_create(&l->pool, st->pool) != APR_SUCCESS) { 
            ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                          "util_ldap: Failed to create memory pool");
#if APR_HAS_THREADS
            apr_thread_mutex_unlock(st->mutex);
#endif
            return NULL;
    
        }
#if APR_HAS_THREADS
        apr_thread_mutex_create(&l->lock, APR_THREAD_MUTEX_DEFAULT, st->pool);
        apr_thread_mutex_lock(l->lock);
#endif
        l->bound = 0;
        l->host = apr_pstrdup(st->pool, host);
        l->port = port;
        l->deref = deref;
        util_ldap_strdup((char**)&(l->binddn), binddn);
        util_ldap_strdup((char**)&(l->bindpw), bindpw);

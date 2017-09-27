        }
    }

/* artificially disable cache */
/* l = NULL; */

    /* If no connection what found after the second search, we
     * must create one.
     */
    if (!l) {

        /*
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

        /* The security mode after parsing the URL will always be either
         * APR_LDAP_NONE (ldap://) or APR_LDAP_SSL (ldaps://).
         * If the security setting is NONE, override it to the security
         * setting optionally supplied by the admin using LDAPTrustedMode
         */
        l->secure = secureflag;

        /* save away a copy of the client cert list that is presently valid */
        l->client_certs = apr_array_copy_hdr(l->pool, st->client_certs);

        /* add the cleanup to the pool */
        apr_pool_cleanup_register(l->pool, l,
                                  uldap_connection_cleanup,
                                  apr_pool_cleanup_null);

        if (p) {
            p->next = l;
        }
        else {
            st->connections = l;

util_ldap_connection_t *util_ldap_connection_find(request_rec *r, const char *host, int port,
                                              const char *binddn, const char *bindpw, deref_options deref,
                                              int netscapessl, int starttls)
{
    struct util_ldap_connection_t *l, *p;	/* To traverse the linked list */

    util_ldap_state_t *st = 
        (util_ldap_state_t *)ap_get_module_config(r->server->module_config,
        &ldap_module);


#if APR_HAS_THREADS
    /* mutex lock this function */
    if (!st->mutex) {
        apr_thread_mutex_create(&st->mutex, APR_THREAD_MUTEX_DEFAULT, st->pool);
    }
    apr_thread_mutex_lock(st->mutex);
#endif

    /* Search for an exact connection match in the list that is not
     * being used.
     */
    for (l=st->connections,p=NULL; l; l=l->next) {
#if APR_HAS_THREADS
        if ( (APR_SUCCESS == apr_thread_mutex_trylock(l->lock)) &&
#else
        if (
#endif
            l->port == port
	    && strcmp(l->host, host) == 0
	    && ( (!l->binddn && !binddn) || (l->binddn && binddn && !strcmp(l->binddn, binddn)) )
	    && ( (!l->bindpw && !bindpw) || (l->bindpw && bindpw && !strcmp(l->bindpw, bindpw)) )
            && l->deref == deref
#ifdef APU_HAS_LDAP_NETSCAPE_SSL
            && l->netscapessl == netscapessl
#endif
#ifdef APU_HAS_LDAP_STARTTLS
	    && l->withtls == starttls
#endif
            )
            break;
        p = l;
    }

    /* If nothing found, search again, but we don't care about the
     * binddn and bindpw this time.
     */
    if (!l) {
        for (l=st->connections,p=NULL; l; l=l->next) {
#if APR_HAS_THREADS
            if ( (APR_SUCCESS == apr_thread_mutex_trylock(l->lock)) &&
#else
            if (
#endif
                l->port == port
	        && strcmp(l->host, host) == 0
                && l->deref == deref
#ifdef APU_HAS_LDAP_NETSCAPE_SSL
                && l->netscapessl == netscapessl
#endif
#ifdef APU_HAS_LDAP_STARTTLS
                && l->withtls == starttls
#endif
                ) {
                /* the bind credentials have changed */
                l->bound = 0;
                l->binddn = apr_pstrdup(st->pool, binddn);
                l->bindpw = apr_pstrdup(st->pool, bindpw);
                break;
            }
            p = l;
        }
    }

/* artificially disable cache */
//l = NULL;

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
#if APR_HAS_THREADS
        apr_thread_mutex_create(&l->lock, APR_THREAD_MUTEX_DEFAULT, st->pool);
        apr_thread_mutex_lock(l->lock);
#endif
        l->pool = st->pool;
        l->bound = 0;
        l->host = apr_pstrdup(st->pool, host);
        l->port = port;
        l->deref = deref;
        l->binddn = apr_pstrdup(st->pool, binddn);
        l->bindpw = apr_pstrdup(st->pool, bindpw);
        l->netscapessl = netscapessl;
        l->starttls = starttls;
        l->withtls = 0;

        if (p) {
            p->next = l;
        }
        else {
            st->connections = l;
        }
    }

#if APR_HAS_THREADS
    apr_thread_mutex_unlock(st->mutex);
#endif
    return l;
}
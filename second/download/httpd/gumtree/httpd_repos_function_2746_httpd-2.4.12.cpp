static util_ldap_connection_t *
            uldap_connection_find(request_rec *r,
                                  const char *host, int port,
                                  const char *binddn, const char *bindpw,
                                  deref_options deref, int secure)
{
    struct util_ldap_connection_t *l, *p; /* To traverse the linked list */
    int secureflag = secure;
    apr_time_t now = apr_time_now();

    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(r->server->module_config,
        &ldap_module);
    util_ldap_config_t *dc =
        (util_ldap_config_t *) ap_get_module_config(r->per_dir_config, &ldap_module);

#if APR_HAS_THREADS
    /* mutex lock this function */
    apr_thread_mutex_lock(st->mutex);
#endif

    if (secure < APR_LDAP_NONE) {
        secureflag = st->secure;
    }

    /* Search for an exact connection match in the list that is not
     * being used.
     */
    for (l=st->connections,p=NULL; l; l=l->next) {
#if APR_HAS_THREADS
        if (APR_SUCCESS == apr_thread_mutex_trylock(l->lock)) {
#endif
        if (   (l->port == port) && (strcmp(l->host, host) == 0)
            && ((!l->binddn && !binddn) || (l->binddn && binddn
                                             && !strcmp(l->binddn, binddn)))
            && ((!l->bindpw && !bindpw) || (l->bindpw && bindpw
                                             && !strcmp(l->bindpw, bindpw)))
            && (l->deref == deref) && (l->secure == secureflag)
            && !compare_client_certs(dc->client_certs, l->client_certs))
        {
            if (st->connection_pool_ttl > 0) {
                if (l->bound && (now - l->last_backend_conn) > st->connection_pool_ttl) {
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                                  "Removing LDAP connection last used %" APR_TIME_T_FMT " seconds ago",
                                  (now - l->last_backend_conn) / APR_USEC_PER_SEC);
                    l->r = r;
                    uldap_connection_unbind(l);
                    /* Go ahead (by falling through) and use it, so we don't create more just to unbind some other old ones */
                }
                ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, 
                              "Reuse %s LDC %pp", 
                              l->bound ? "bound" : "unbound", l);
            }
            break;
        }
#if APR_HAS_THREADS
            /* If this connection didn't match the criteria, then we
             * need to unlock the mutex so it is available to be reused.
             */
            apr_thread_mutex_unlock(l->lock);
        }
#endif
        p = l;
    }

    /* If nothing found, search again, but we don't care about the
     * binddn and bindpw this time.
     */
    if (!l) {
        for (l=st->connections,p=NULL; l; l=l->next) {
#if APR_HAS_THREADS
            if (APR_SUCCESS == apr_thread_mutex_trylock(l->lock)) {

#endif
            if ((l->port == port) && (strcmp(l->host, host) == 0) &&
                (l->deref == deref) && (l->secure == secureflag) &&
                !compare_client_certs(dc->client_certs, l->client_certs))
            {
                if (st->connection_pool_ttl > 0) {
                    if (l->bound && (now - l->last_backend_conn) > st->connection_pool_ttl) {
                        ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                                "Removing LDAP connection last used %" APR_TIME_T_FMT " seconds ago",
                                (now - l->last_backend_conn) / APR_USEC_PER_SEC);
                        l->r = r;
                        uldap_connection_unbind(l);
                        /* Go ahead (by falling through) and use it, so we don't create more just to unbind some other old ones */
                    }
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, 
                                  "Reuse %s LDC %pp (will rebind)", 
                                   l->bound ? "bound" : "unbound", l);
                }

                /* the bind credentials have changed
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
                if (l->bound && (now - l->freed) > st->connection_pool_ttl) {
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                                  "Removing LDAP connection last used %" APR_TIME_T_FMT " seconds ago",
                                  (now - l->freed) / APR_USEC_PER_SEC);
                    uldap_connection_unbind(l);
                    /* Go ahead (by falling through) and use it, so we don't create more just to unbind some other old ones */
                }
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
                /* the bind credentials have changed */
                /* no check for connection_pool_ttl, since we are unbinding any way */
                uldap_connection_unbind(l);

                util_ldap_strdup((char**)&(l->binddn), binddn);
                util_ldap_strdup((char**)&(l->bindpw), bindpw);
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
    }

/* artificially disable cache */
/* l = NULL; */

    /* If no connection was found after the second search, we
     * must create one.
     */
    if (!l) {
        apr_pool_t *newpool;
        if (apr_pool_create(&newpool, NULL) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01285)
                          "util_ldap: Failed to create memory pool");
#if APR_HAS_THREADS
            apr_thread_mutex_unlock(st->mutex);
#endif
            return NULL;
        }

        /*
         * Add the new connection entry to the linked list. Note that we
         * don't actually establish an LDAP connection yet; that happens
         * the first time authentication is requested.
         */

        /* create the details of this connection in the new pool */
        l = apr_pcalloc(newpool, sizeof(util_ldap_connection_t));
        l->pool = newpool;
        l->st = st;

#if APR_HAS_THREADS
        apr_thread_mutex_create(&l->lock, APR_THREAD_MUTEX_DEFAULT, l->pool);
        apr_thread_mutex_lock(l->lock);
#endif
        l->bound = 0;
        l->host = apr_pstrdup(l->pool, host);
        l->port = port;
        l->deref = deref;
        util_ldap_strdup((char**)&(l->binddn), binddn);
        util_ldap_strdup((char**)&(l->bindpw), bindpw);
        l->ChaseReferrals = dc->ChaseReferrals;
        l->ReferralHopLimit = dc->ReferralHopLimit;

        /* The security mode after parsing the URL will always be either
         * APR_LDAP_NONE (ldap://) or APR_LDAP_SSL (ldaps://).
         * If the security setting is NONE, override it to the security
         * setting optionally supplied by the admin using LDAPTrustedMode
         */
        l->secure = secureflag;

        /* save away a copy of the client cert list that is presently valid */
        l->client_certs = apr_array_copy_hdr(l->pool, dc->client_certs);

        /* whether or not to keep this connection in the pool when it's returned */
        l->keep = (st->connection_pool_ttl == 0) ? 0 : 1;

        if (l->ChaseReferrals == AP_LDAP_CHASEREFERRALS_ON) {
            if (apr_pool_create(&(l->rebind_pool), l->pool) != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01286)
                              "util_ldap: Failed to create memory pool");
#if APR_HAS_THREADS
                apr_thread_mutex_unlock(st->mutex);
#endif
                return NULL;
            }
        }

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
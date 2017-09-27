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

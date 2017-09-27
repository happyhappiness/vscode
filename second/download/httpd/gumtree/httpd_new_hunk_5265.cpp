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

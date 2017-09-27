        st->opTimeout->tv_sec = timeout;
    }
    else {
        st->opTimeout = NULL;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "ldap connection: Setting op timeout to %ld seconds.",
                 timeout);

#ifndef LDAP_OPT_TIMEOUT

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "LDAP: LDAP_OPT_TIMEOUT option not supported by the "
                 "LDAP library in use. Using LDAPTimeout value as search "
                 "timeout only." );
#endif

    return NULL;
}



static void *util_ldap_create_config(apr_pool_t *p, server_rec *s)
{
    util_ldap_state_t *st =
        (util_ldap_state_t *)apr_pcalloc(p, sizeof(util_ldap_state_t));

    /* Create a per vhost pool for mod_ldap to use, serialized with 
     * st->mutex (also one per vhost).  both are replicated by fork(),
     * no shared memory managed by either.
     */
    apr_pool_create(&st->pool, p);
#if APR_HAS_THREADS
    apr_thread_mutex_create(&st->mutex, APR_THREAD_MUTEX_DEFAULT, st->pool);

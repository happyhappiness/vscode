    }

#ifdef LDAP_OPT_NETWORK_TIMEOUT
    st->connectionTimeout = atol(ttl);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "[%" APR_PID_T_FMT "] ldap connection: Setting connection timeout to "
                 "%ld seconds.", getpid(), st->connectionTimeout);
#else
    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, cmd->server,
                 "LDAP: Connection timout option not supported by the "
                 "LDAP SDK in use." );
#endif

    return NULL;
}


static void *util_ldap_create_config(apr_pool_t *p, server_rec *s)
{
    util_ldap_state_t *st =
        (util_ldap_state_t *)apr_pcalloc(p, sizeof(util_ldap_state_t));

    /* Create a per vhost pool for mod_ldap to use, serialized with 
     * st->mutex (also one per vhost) 
     */
    apr_pool_create(&st->pool, p);
#if APR_HAS_THREADS
    apr_thread_mutex_create(&st->mutex, APR_THREAD_MUTEX_DEFAULT, st->pool);
#endif


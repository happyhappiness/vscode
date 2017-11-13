static const char *util_ldap_set_connection_timeout(cmd_parms *cmd,
                                                    void *dummy,
                                                    const char *ttl)
{
#ifdef LDAP_OPT_NETWORK_TIMEOUT
    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
                                                  &ldap_module);
#endif
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
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
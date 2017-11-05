static const char *util_ldap_set_op_timeout(cmd_parms *cmd,
                                            void *dummy,
                                            const char *val)
{
    long timeout;
    char *endptr;
    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
                                                  &ldap_module);
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    timeout = strtol(val, &endptr, 10);
    if ((val == endptr) || (*endptr != '\0')) {
        return "Timeout not numerical";
    }
    if (timeout < 0) {
        return "Timeout must be non-negative";
    }

    if (timeout) {
        if (!st->opTimeout) {
            st->opTimeout = apr_pcalloc(cmd->pool, sizeof(struct timeval));
        }
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
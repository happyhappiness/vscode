static const char *util_ldap_set_conn_ttl(cmd_parms *cmd,
                                          void *dummy,
                                          const char *val)
{
    apr_interval_time_t timeout;
    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
                                                  &ldap_module);

    if (ap_timeout_parameter_parse(val, &timeout, "s") != APR_SUCCESS) {
        return "LDAPConnectionPoolTTL has wrong format";
    }

    if (timeout < 0) {
        /* reserve -1 for default value */
        timeout = AP_LDAP_CONNPOOL_INFINITE;
    }
    st->connection_pool_ttl = timeout;
    return NULL;
}
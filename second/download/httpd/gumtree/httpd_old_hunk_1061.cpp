static const char *util_ldap_set_cache_bytes(cmd_parms *cmd, void *dummy,
                                             const char *bytes)
{
    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
                                                  &ldap_module);

    st->cache_bytes = atol(bytes);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "[%" APR_PID_T_FMT "] ldap cache: Setting shared memory "
                 " cache size to %" APR_SIZE_T_FMT " bytes.",

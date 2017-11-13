static const char *util_ldap_set_cache_bytes(cmd_parms *cmd, void *dummy,
                                             const char *bytes)
{
    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
                                                  &ldap_module);
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    st->cache_bytes = atol(bytes);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "ldap cache: Setting shared memory cache size to "
                 "%" APR_SIZE_T_FMT " bytes.",
                 st->cache_bytes);

    return NULL;
}
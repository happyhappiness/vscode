static const char *util_ldap_set_cache_entries(cmd_parms *cmd, void *dummy,
                                               const char *size)
{
    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
                                                  &ldap_module);
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    st->search_cache_size = atol(size);
    if (st->search_cache_size < 0) {
        st->search_cache_size = 0;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01300)
                 "ldap cache: Setting search cache size to %ld entries.",
                 st->search_cache_size);

    return NULL;
}
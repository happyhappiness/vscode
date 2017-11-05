static const char *util_ldap_set_cache_file(cmd_parms *cmd, void *dummy,
                                            const char *file)
{
    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
                                                  &ldap_module);
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    if (file) {
        st->cache_file = ap_server_root_relative(st->pool, file);
    }
    else {
        st->cache_file = NULL;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01298)
                 "LDAP cache: Setting shared memory cache file to %s bytes.",
                 st->cache_file);

    return NULL;
}
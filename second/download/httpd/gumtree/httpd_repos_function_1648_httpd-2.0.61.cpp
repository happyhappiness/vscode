static const char *util_ldap_set_cache_entries(cmd_parms *cmd, void *dummy, const char *size)
{
    util_ldap_state_t *st = 
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config, 
						  &ldap_module);


    st->search_cache_size = atol(size);
    if (st->search_cache_size < 0) {
        st->search_cache_size = 0;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, cmd->server, 
                      "[%d] ldap cache: Setting search cache size to %ld entries.", 
                      getpid(), st->search_cache_size);

    return NULL;
}
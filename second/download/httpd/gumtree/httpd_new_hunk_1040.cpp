                      "[%d] ldap cache: Setting shared memory cache size to %d bytes.", 
                      getpid(), st->cache_bytes);

    return NULL;
}

static const char *util_ldap_set_cache_file(cmd_parms *cmd, void *dummy, const char *file)
{
    util_ldap_state_t *st = 
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config, 
                                                  &ldap_module);

    if (file) {
        st->cache_file = ap_server_root_relative(st->pool, file);
    }
    else {
        st->cache_file = NULL;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, cmd->server, 
                 "LDAP cache: Setting shared memory cache file to %s bytes.", 
                 st->cache_file);

    return NULL;
}

static const char *util_ldap_set_cache_ttl(cmd_parms *cmd, void *dummy, const char *ttl)
{
    util_ldap_state_t *st = 
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config, 
						  &ldap_module);


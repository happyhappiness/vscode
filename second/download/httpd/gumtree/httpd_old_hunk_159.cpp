                      "[%d] ldap cache: Setting shared memory cache size to %d bytes.", 
                      getpid(), st->cache_bytes);

    return NULL;
}

static const char *util_ldap_set_cache_ttl(cmd_parms *cmd, void *dummy, const char *ttl)
{
    util_ldap_state_t *st = 
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config, 
						  &ldap_module);


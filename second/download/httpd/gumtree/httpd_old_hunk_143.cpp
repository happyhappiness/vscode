                      "[%d] ldap cache: Setting operation cache size to %ld entries.", 
                      getpid(), st->compare_cache_size);

    return NULL;
}

#ifdef APU_HAS_LDAP_NETSCAPE_SSL
static const char *util_ldap_set_certdbpath(cmd_parms *cmd, void *dummy, const char *path)
{
    util_ldap_state_t *st = 
        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config, 
						  &ldap_module);

    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, cmd->server, 
                      "[%d] ldap cache: Setting LDAP SSL client certificate dbpath to %s.", 
                      getpid(), path);

    st->have_certdb = 1;
    if (ldapssl_client_init(path, NULL) != 0) {
        return "Could not initialize SSL client";
    }
    else {
        return NULL;
    }
}
#endif

void *util_ldap_create_config(apr_pool_t *p, server_rec *s)
{
    util_ldap_state_t *st = 
        (util_ldap_state_t *)apr_pcalloc(p, sizeof(util_ldap_state_t));


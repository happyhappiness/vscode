static apr_status_t util_ldap_cleanup_module(void *data)
{
#if APR_HAS_LDAP_SSL && APR_HAS_NOVELL_LDAPSDK
    server_rec *s = data;
    util_ldap_state_t *st = (util_ldap_state_t *)ap_get_module_config(
        s->module_config, &ldap_module);
    
    if (st->ssl_support)
        ldapssl_client_deinit();

#endif
    return APR_SUCCESS;
}
static apr_status_t util_ldap_cleanup_module(void *data)
{

    server_rec *s = data;
    util_ldap_state_t *st = (util_ldap_state_t *)ap_get_module_config(
        s->module_config, &ldap_module);

    if (st->ssl_supported) {
        apr_ldap_ssl_deinit();
    }

    return APR_SUCCESS;

}
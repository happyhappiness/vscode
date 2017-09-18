    st->cert_file_type = LDAP_CA_TYPE_UNKNOWN;
    st->ssl_support = 0;

    return st;
}

static apr_status_t util_ldap_cleanup_module(void *data)
{
    server_rec *s = data;

    util_ldap_state_t *st = (util_ldap_state_t *)ap_get_module_config(
                                          s->module_config, &ldap_module);

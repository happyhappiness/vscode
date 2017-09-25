    else
        st->cert_file_type = LDAP_CA_TYPE_UNKNOWN;

    return(NULL);
}


void *util_ldap_create_config(apr_pool_t *p, server_rec *s)
{
    util_ldap_state_t *st = 
        (util_ldap_state_t *)apr_pcalloc(p, sizeof(util_ldap_state_t));


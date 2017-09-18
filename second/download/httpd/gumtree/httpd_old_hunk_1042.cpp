}

static int util_ldap_post_config(apr_pool_t *p, apr_pool_t *plog, 
                                 apr_pool_t *ptemp, server_rec *s)
{
    int rc = LDAP_SUCCESS;

    util_ldap_state_t *st = (util_ldap_state_t *)ap_get_module_config(
                                                s->module_config, 
                                                &ldap_module);

        /* log the LDAP SDK used 
        */
    #if APR_HAS_NETSCAPE_LDAPSDK 
    
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
             "LDAP: Built with Netscape LDAP SDK" );

    #elif APR_HAS_NOVELL_LDAPSDK

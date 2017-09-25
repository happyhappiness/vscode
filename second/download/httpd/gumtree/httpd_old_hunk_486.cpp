    else
    {
       ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
                         "LDAP: SSL support unavailable" );
    }
    
    return(OK);
}

static void util_ldap_child_init(apr_pool_t *p, server_rec *s)
{
    apr_status_t sts;

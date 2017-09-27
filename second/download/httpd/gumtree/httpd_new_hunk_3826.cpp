        log_tracing_state(ssl, c, s, where, rc);
    }
}

#ifdef HAVE_TLSEXT
/*
 * This function sets the virtual host from an extended
 * client hello with a server name indication extension ("SNI", cf. RFC 6066).
 */
static apr_status_t init_vhost(conn_rec *c, SSL *ssl)
{
    const char *servername;
    
    if (c) {
        SSLConnRec *sslcon = myConnConfig(c);
        
        if (sslcon->server != c->base_server) {
            /* already found the vhost */
            return APR_SUCCESS;
        }
        
        servername = SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name);
        if (servername) {
            if (ap_vhost_iterate_given_conn(c, ssl_find_vhost,
                                            (void *)servername)) {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(02043)
                              "SSL virtual host for servername %s found",
                              servername);
                return APR_SUCCESS;
            }
            else {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(02044)
                              "No matching SSL virtual host for servername "
                              "%s found (using default/first virtual host)",
                              servername);

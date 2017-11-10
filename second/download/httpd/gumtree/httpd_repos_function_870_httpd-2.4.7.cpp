int ssl_hook_Fixup(request_rec *r)
{
    SSLConnRec *sslconn = myConnConfig(r->connection);
    SSLSrvConfigRec *sc = mySrvConfig(r->server);
    SSLDirConfigRec *dc = myDirConfig(r);
    apr_table_t *env = r->subprocess_env;
    char *var, *val = "";
#ifdef HAVE_TLSEXT
    const char *servername;
#endif
    STACK_OF(X509) *peer_certs;
    SSL *ssl;
    int i;

    /* If "SSLEngine optional" is configured, this is not an SSL
     * connection, and this isn't a subrequest, send an Upgrade
     * response header. */
    if (sc->enabled == SSL_ENABLED_OPTIONAL && !(sslconn && sslconn->ssl)
        && !r->main) {
        apr_table_setn(r->headers_out, "Upgrade", "TLS/1.0, HTTP/1.1");
        apr_table_mergen(r->headers_out, "Connection", "upgrade");
    }

    /*
     * Check to see if SSL is on
     */
    if (!(((sc->enabled == SSL_ENABLED_TRUE) || (sc->enabled == SSL_ENABLED_OPTIONAL)) && sslconn && (ssl = sslconn->ssl))) {
        return DECLINED;
    }

    /*
     * Annotate the SSI/CGI environment with standard SSL information
     */
    /* the always present HTTPS (=HTTP over SSL) flag! */
    apr_table_setn(env, "HTTPS", "on");

#ifdef HAVE_TLSEXT
    /* add content of SNI TLS extension (if supplied with ClientHello) */
    if ((servername = SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name))) {
        apr_table_set(env, "SSL_TLS_SNI", servername);
    }
#endif

    /* standard SSL environment variables */
    if (dc->nOptions & SSL_OPT_STDENVVARS) {
        modssl_var_extract_dns(env, sslconn->ssl, r->pool);

        for (i = 0; ssl_hook_Fixup_vars[i]; i++) {
            var = (char *)ssl_hook_Fixup_vars[i];
            val = ssl_var_lookup(r->pool, r->server, r->connection, r, var);
            if (!strIsEmpty(val)) {
                apr_table_setn(env, var, val);
            }
        }
    }

    /*
     * On-demand bloat up the SSI/CGI environment with certificate data
     */
    if (dc->nOptions & SSL_OPT_EXPORTCERTDATA) {
        val = ssl_var_lookup(r->pool, r->server, r->connection,
                             r, "SSL_SERVER_CERT");

        apr_table_setn(env, "SSL_SERVER_CERT", val);

        val = ssl_var_lookup(r->pool, r->server, r->connection,
                             r, "SSL_CLIENT_CERT");

        apr_table_setn(env, "SSL_CLIENT_CERT", val);

        if ((peer_certs = (STACK_OF(X509) *)SSL_get_peer_cert_chain(ssl))) {
            for (i = 0; i < sk_X509_num(peer_certs); i++) {
                var = apr_psprintf(r->pool, "SSL_CLIENT_CERT_CHAIN_%d", i);
                val = ssl_var_lookup(r->pool, r->server, r->connection,
                                     r, var);
                if (val) {
                    apr_table_setn(env, var, val);
                }
            }
        }
    }


#ifdef SSL_get_secure_renegotiation_support
    apr_table_setn(r->notes, "ssl-secure-reneg",
                   SSL_get_secure_renegotiation_support(ssl) ? "1" : "0");
#endif

    return DECLINED;
}
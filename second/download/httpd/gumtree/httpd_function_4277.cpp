static apr_uri_t *determine_responder_uri(SSLSrvConfigRec *sc, X509 *cert, 
                                          conn_rec *c, apr_pool_t *p)
{
    apr_uri_t *u = apr_palloc(p, sizeof *u);
    const char *s;
    apr_status_t rv;

    /* Use default responder URL if forced by configuration, else use
     * certificate-specified responder, falling back to default if
     * necessary and possible. */
    if (sc->server->ocsp_force_default) {
        s = sc->server->ocsp_responder;
    }
    else {
        s = extract_responder_uri(cert, p); 

        if (s == NULL && sc->server->ocsp_responder) {
            s = sc->server->ocsp_responder;
        }
    }

    if (s == NULL) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                      "no OCSP responder specified in certificate and "
                      "no default configured");
        return NULL;
    }

    rv = apr_uri_parse(p, s, u);
    if (rv || !u->hostname) {    
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rv, c, 
                      "failed to parse OCSP responder URI '%s'", s);
        return NULL;
    }

    if (strcasecmp(u->scheme, "http") != 0) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rv, c, 
                      "cannot handle OCSP responder URI '%s'", s);
        return NULL;
    }

    if (!u->port) {
        u->port = apr_uri_port_of_scheme(u->scheme);
    }

    return u;
}
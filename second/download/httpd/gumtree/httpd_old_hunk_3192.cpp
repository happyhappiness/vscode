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

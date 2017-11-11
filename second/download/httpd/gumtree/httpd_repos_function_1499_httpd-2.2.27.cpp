static int proxy_detect(request_rec *r)
{
    void *sconf = r->server->module_config;
    proxy_server_conf *conf =
        (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);

    /* Ick... msvc (perhaps others) promotes ternary short results to int */

    if (conf->req && r->parsed_uri.scheme) {
        /* but it might be something vhosted */
        if (!(r->parsed_uri.hostname
              && !strcasecmp(r->parsed_uri.scheme, ap_http_scheme(r))
              && ap_matches_request_vhost(r, r->parsed_uri.hostname,
                                          (apr_port_t)(r->parsed_uri.port_str ? r->parsed_uri.port
                                                       : ap_default_port(r))))) {
            r->proxyreq = PROXYREQ_PROXY;
            r->uri = r->unparsed_uri;
            r->filename = apr_pstrcat(r->pool, "proxy:", r->uri, NULL);
            r->handler = "proxy-server";
        }
    }
    /* We need special treatment for CONNECT proxying: it has no scheme part */
    else if (conf->req && r->method_number == M_CONNECT
             && r->parsed_uri.hostname
             && r->parsed_uri.port_str) {
        r->proxyreq = PROXYREQ_PROXY;
        r->uri = r->unparsed_uri;
        r->filename = apr_pstrcat(r->pool, "proxy:", r->uri, NULL);
        r->handler = "proxy-server";
    }
    return DECLINED;
}
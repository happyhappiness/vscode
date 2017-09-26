AP_DECLARE(apr_port_t) ap_get_server_port(const request_rec *r)
{
    apr_port_t port;
    core_dir_config *d =
      (core_dir_config *)ap_get_module_config(r->per_dir_config, &core_module);

    if (d->use_canonical_name == USE_CANONICAL_NAME_OFF
        || d->use_canonical_name == USE_CANONICAL_NAME_DNS) {

        /* With UseCanonicalName off Apache will form self-referential
         * URLs using the hostname and port supplied by the client if
         * any are supplied (otherwise it will use the canonical name).
         */
        port = r->parsed_uri.port_str ? r->parsed_uri.port :
               r->server->port ? r->server->port :
               ap_default_port(r);
    }
    else { /* d->use_canonical_name == USE_CANONICAL_NAME_ON */

        /* With UseCanonicalName on (and in all versions prior to 1.3)
         * Apache will use the hostname and port specified in the
         * ServerName directive to construct a canonical name for the
         * server. (If no port was specified in the ServerName
         * directive, Apache uses the port supplied by the client if
         * any is supplied, and finally the default port for the protocol
         * used.
         */
        port = r->server->port ? r->server->port :
               r->connection->local_addr->port ? r->connection->local_addr->port :
               ap_default_port(r);
    }

    /* default */
    return port;
}

AP_DECLARE(char *) ap_construct_url(apr_pool_t *p, const char *uri,
                                    request_rec *r)
{
    unsigned port = ap_get_server_port(r);
    const char *host = get_server_name_for_url(r);

    if (ap_is_default_port(port, r)) {
        return apr_pstrcat(p, ap_http_method(r), "://", host, uri, NULL);
    }

    return apr_psprintf(p, "%s://%s:%u%s", ap_http_method(r), host, port, uri);
}

AP_DECLARE(apr_off_t) ap_get_limit_req_body(const request_rec *r)
{
    core_dir_config *d =
      (core_dir_config *)ap_get_module_config(r->per_dir_config, &core_module);

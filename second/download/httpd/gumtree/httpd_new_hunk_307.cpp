     * for the HTTP port or vice versa
     */
    for (s = base_server; s; s = s->next) {
        sc = mySrvConfig(s);

        if (sc->enabled && (s->port == DEFAULT_HTTP_PORT)) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                         base_server,
                         "Init: (%s) You configured HTTPS(%d) "
                         "on the standard HTTP(%d) port!",
                         ssl_util_vhostid(p, s),
                         DEFAULT_HTTPS_PORT, DEFAULT_HTTP_PORT);
        }

        if (!sc->enabled && (s->port == DEFAULT_HTTPS_PORT)) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                         base_server,
                         "Init: (%s) You configured HTTP(%d) "
                         "on the standard HTTPS(%d) port!",
                         ssl_util_vhostid(p, s),
                         DEFAULT_HTTP_PORT, DEFAULT_HTTPS_PORT);
        }
    }

    /*
     * Give out warnings when more than one SSL-aware virtual server uses the
     * same IP:port. This doesn't work because mod_ssl then will always use

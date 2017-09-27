     * Make really sure that when a peer certificate
     * is required we really got one... (be paranoid)
     */
    if ((sc->server->auth.verify_mode == SSL_CVERIFY_REQUIRE) &&
        !sslconn->client_cert)
    {
        ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                      "No acceptable peer certificate available");

        ssl_filter_io_shutdown(filter_ctx, c, 1);
        return APR_ECONNABORTED;
    }


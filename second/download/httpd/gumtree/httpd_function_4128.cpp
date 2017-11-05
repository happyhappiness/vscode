static int ssl_hook_pre_connection(conn_rec *c, void *csd)
{
    SSLSrvConfigRec *sc;
    SSLConnRec *sslconn = myConnConfig(c);

    if (sslconn) {
        sc = mySrvConfig(sslconn->server);
    }
    else {
        sc = mySrvConfig(c->base_server);
    }
    /*
     * Immediately stop processing if SSL is disabled for this connection
     */
    if (!(sc && (sc->enabled == SSL_ENABLED_TRUE ||
                 (sslconn && sslconn->is_proxy))))
    {
        return DECLINED;
    }

    /*
     * Create SSL context
     */
    if (!sslconn) {
        sslconn = ssl_init_connection_ctx(c);
    }

    if (sslconn->disabled) {
        return DECLINED;
    }

    /*
     * Remember the connection information for
     * later access inside callback functions
     */

    ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                  "Connection to child %ld established "
                  "(server %s)", c->id, sc->vhost_id);

    return ssl_init_ssl_connection(c, NULL);
}
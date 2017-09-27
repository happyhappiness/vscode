     */

    ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                  "Connection to child %ld established "
                  "(server %s)", c->id, sc->vhost_id);

    return ssl_init_ssl_connection(c);
}


static void ssl_hook_Insert_Filter(request_rec *r)
{
    SSLSrvConfigRec *sc = mySrvConfig(r->server);

    if (sc->enabled == SSL_ENABLED_OPTIONAL) {
        ap_add_output_filter("UPGRADE_FILTER", NULL, r, r->connection);
    }
}

/*
 *  the module registration phase
 */


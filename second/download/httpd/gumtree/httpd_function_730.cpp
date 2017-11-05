static void ssl_hook_Insert_Filter(request_rec *r)
{
    SSLSrvConfigRec *sc = mySrvConfig(r->server);

    if (sc->enabled == SSL_ENABLED_OPTIONAL) {
        ap_add_output_filter("UPGRADE_FILTER", NULL, r, r->connection);
    }
}
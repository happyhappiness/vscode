static void ssl_hook_Insert_Filter(request_rec *r)
{
    NWSSLSrvConfigRec *sc = get_nwssl_cfg(r->server);

    if (isSecureUpgradeable (r)) {
        ap_add_output_filter("UPGRADE_FILTER", NULL, r, r->connection);
    }
}
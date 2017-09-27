                 modver, AP_SERVER_BASEVERSION, incver);
}

/*
 *  Per-module initialization
 */
apr_status_t ssl_init_Module(apr_pool_t *p, apr_pool_t *plog,
                             apr_pool_t *ptemp,
                             server_rec *base_server)
{
    SSLModConfigRec *mc = myModConfig(base_server);
    SSLSrvConfigRec *sc;
    server_rec *s;
    apr_status_t rv;
    apr_array_header_t *pphrases;

    if (SSLeay() < SSL_LIBRARY_VERSION) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server, APLOGNO(01882)
                     "Init: this version of mod_ssl was compiled against "
                     "a newer library (%s, version currently loaded is %s)"
                     " - may result in undefined or erroneous behavior",

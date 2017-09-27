/*  _________________________________________________________________
**
**  Module Initialization
**  _________________________________________________________________
*/


static void ssl_add_version_components(apr_pool_t *p,
                                       server_rec *s)
{
    char *modver = ssl_var_lookup(p, s, NULL, NULL, "SSL_VERSION_INTERFACE");
    char *libver = ssl_var_lookup(p, s, NULL, NULL, "SSL_VERSION_LIBRARY");
    char *incver = ssl_var_lookup(p, s, NULL, NULL, 
                                  "SSL_VERSION_LIBRARY_INTERFACE");

    ap_add_version_component(p, modver);
    ap_add_version_component(p, libver);

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "%s compiled against Server: %s, Library: %s",
                 modver, AP_SERVER_BASEVERSION, incver);
}


/*
 *  Initialize SSL library
 */

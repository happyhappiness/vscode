 *  ssl_engine_init.c
 *  Initialization of Servers
 */
                             /* ``Recursive, adj.;
                                  see Recursive.''
                                        -- Unknown   */
#include "mod_ssl.h"

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
static void ssl_init_SSLLibrary(server_rec *s)
{
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "Init: Initializing %s library", SSL_LIBRARY_NAME);

    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms(); /* Required for eg SHA256 client certs */
}

/*
 * Handle the Temporary RSA Keys and DH Params
 */

#define MODSSL_TMP_KEY_FREE(mc, type, idx) \
    if (mc->pTmpKeys[idx]) { \

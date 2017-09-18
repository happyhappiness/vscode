 */
                             /* ``Real programmers confuse
                                  Christmas and Halloween
                                  because DEC 25 = OCT 31.''
                                             -- Unknown     */
#include "mod_ssl.h"
#if !defined(OS2) && !defined(WIN32) && !defined(BEOS) && !defined(NETWARE)
#include "unixd.h"
#endif

int ssl_mutex_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_status_t rv;

    if (mc->nMutexMode == SSL_MUTEXMODE_NONE) 
        return TRUE;

    if ((rv = apr_global_mutex_create(&mc->pMutex, mc->szMutexFile,
                                APR_LOCK_DEFAULT, p)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Cannot create SSLMutex file `%s'",
                     mc->szMutexFile);
        return FALSE;
    }

#if APR_USE_SYSVSEM_SERIALIZE
    rv = unixd_set_global_mutex_perms(mc->pMutex);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Could not set permissions on ssl_mutex; check User "
                     "and Group directives");
        return FALSE;
    }
#endif
    return TRUE;
}

int ssl_mutex_reinit(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);

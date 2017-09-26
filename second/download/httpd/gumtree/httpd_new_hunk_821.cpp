 */
                             /* ``Real programmers confuse
                                  Christmas and Halloween
                                  because DEC 25 = OCT 31.''
                                             -- Unknown     */

#include "ssl_private.h"

#ifdef AP_NEED_SET_MUTEX_PERMS
#include "unixd.h"
#endif

int ssl_mutex_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_status_t rv;

    if (mc->nMutexMode == SSL_MUTEXMODE_NONE)
        return TRUE;

    if (mc->pMutex) {
        return TRUE;
    }
    if ((rv = apr_global_mutex_create(&mc->pMutex, mc->szMutexFile,
                                      mc->nMutexMech, s->process->pool))
            != APR_SUCCESS) {
        if (mc->szMutexFile)
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Cannot create SSLMutex with file `%s'",
                         mc->szMutexFile);
        else
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Cannot create SSLMutex");
        return FALSE;
    }

#ifdef AP_NEED_SET_MUTEX_PERMS
    rv = unixd_set_global_mutex_perms(mc->pMutex);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Could not set permissions on ssl_mutex; check User "
                     "and Group directives");
        return FALSE;

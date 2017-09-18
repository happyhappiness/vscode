 */
                             /* ``Real programmers confuse
                                  Christmas and Halloween
                                  because DEC 25 = OCT 31.''
                                             -- Unknown     */
#include "mod_ssl.h"

int ssl_mutex_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (mc->nMutexMode == SSL_MUTEXMODE_NONE) 
        return TRUE;

    if (apr_global_mutex_create(&mc->pMutex, mc->szMutexFile,
                                APR_LOCK_DEFAULT, p) != APR_SUCCESS) {
        ssl_log(s, SSL_LOG_ERROR,
                   "Cannot create SSLMutex file `%s'",
                    mc->szMutexFile);
        return FALSE;
    }
    return TRUE;
}

int ssl_mutex_reinit(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);

                                  Christmas and Halloween
                                  because DEC 25 = OCT 31.''
                                             -- Unknown     */

#include "ssl_private.h"

int ssl_mutex_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_status_t rv;

    /* A mutex is only needed if a session cache is configured, and
     * the provider used is not internally multi-process/thread
     * safe. */
    if (!mc->sesscache
        || (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) == 0) {
        return TRUE;
    }

    if (mc->pMutex) {
        return TRUE;
    }

    if ((rv = ap_global_mutex_create(&mc->pMutex, NULL, SSL_CACHE_MUTEX_TYPE,
                                     NULL, s, s->process->pool, 0))
            != APR_SUCCESS) {
        return FALSE;
    }

    return TRUE;
}

int ssl_mutex_reinit(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_status_t rv;
    const char *lockfile;

    if (mc->pMutex == NULL || !mc->sesscache
        || (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) == 0) {
        return TRUE;
    }

    lockfile = apr_global_mutex_lockfile(mc->pMutex);
    if ((rv = apr_global_mutex_child_init(&mc->pMutex,
                                          lockfile,
                                          p)) != APR_SUCCESS) {
        if (lockfile)
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Cannot reinit %s mutex with file `%s'",
                         SSL_CACHE_MUTEX_TYPE, lockfile);
        else
            ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s,
                         "Cannot reinit %s mutex", SSL_CACHE_MUTEX_TYPE);
        return FALSE;
    }
    return TRUE;
}

int ssl_mutex_on(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_status_t rv;

    if ((rv = apr_global_mutex_lock(mc->pMutex)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s,
                     "Failed to acquire SSL session cache lock");
        return FALSE;
    }
    return TRUE;

#include "mod_ssl.h"

void ssl_scache_dbm_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_dbm_t *dbm;
    apr_status_t rv;

    /* for the DBM we need the data file */
    if (mc->szSessionCacheDataFile == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "SSLSessionCache required");
        ssl_die();
    }

    /* open it once to create it and to make sure it _can_ be created */
    ssl_mutex_on(s);
    if ((rv = apr_dbm_open(&dbm, mc->szSessionCacheDataFile,
	    APR_DBM_RWCREATE, SSL_DBM_FILE_MODE, mc->pPool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Cannot create SSLSessionCache DBM file `%s'",
                     mc->szSessionCacheDataFile);
        ssl_mutex_off(s);
        return;
    }
    apr_dbm_close(dbm);

#if !defined(OS2) && !defined(WIN32) && !defined(BEOS) && !defined(NETWARE)

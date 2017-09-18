#include "mod_ssl.h"

void ssl_scache_dbm_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_dbm_t *dbm;

    /* for the DBM we need the data file */
    if (mc->szSessionCacheDataFile == NULL) {
        ssl_log(s, SSL_LOG_ERROR, "SSLSessionCache required");
        ssl_die();
    }

    /* open it once to create it and to make sure it _can_ be created */
    ssl_mutex_on(s);
    if (apr_dbm_open(&dbm, mc->szSessionCacheDataFile,
	    APR_DBM_RWCREATE, SSL_DBM_FILE_MODE, mc->pPool) != APR_SUCCESS) {
        ssl_log(s, SSL_LOG_ERROR|SSL_ADD_ERRNO,
                "Cannot create SSLSessionCache DBM file `%s'",
                mc->szSessionCacheDataFile);
        ssl_mutex_off(s);
        return;
    }
    apr_dbm_close(dbm);

#if !defined(OS2) && !defined(WIN32) && !defined(BEOS) && !defined(NETWARE)

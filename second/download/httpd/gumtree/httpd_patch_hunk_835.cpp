                  "Inter-Process Session Cache (DBM) Expiry: "
                  "old: %d, new: %d, removed: %d",
                  nElements, nElements-nDeleted, nDeleted);
     return;
 }
 
-void ssl_scache_dbm_status(server_rec *s, apr_pool_t *p, void (*func)(char *, void *), void *arg)
+void ssl_scache_dbm_status(request_rec *r, int flags, apr_pool_t *p)
 {
-    SSLModConfigRec *mc = myModConfig(s);
+    SSLModConfigRec *mc = myModConfig(r->server);
     apr_dbm_t *dbm;
     apr_datum_t dbmkey;
     apr_datum_t dbmval;
     int nElem;
     int nSize;
     int nAverage;
     apr_status_t rv;
 
     nElem = 0;
     nSize = 0;
-    ssl_mutex_on(s);
+    ssl_mutex_on(r->server);
     /*
      * XXX - Check what pool is to be used - TBD
      */
     if ((rv = apr_dbm_open(&dbm, mc->szSessionCacheDataFile,
 	                       APR_DBM_RWCREATE, SSL_DBM_FILE_MODE,
                            mc->pPool)) != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "Cannot open SSLSessionCache DBM file `%s' for status "
                      "retrival",
                      mc->szSessionCacheDataFile);
-        ssl_mutex_off(s);
+        ssl_mutex_off(r->server);
         return;
     }
     /*
      * XXX - Check the return value of apr_dbm_firstkey, apr_dbm_fetch - TBD
      */
     apr_dbm_firstkey(dbm, &dbmkey);

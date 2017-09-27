 **  _________________________________________________________________
 */
 
 void ssl_scache_init(server_rec *s, apr_pool_t *p)
 {
     SSLModConfigRec *mc = myModConfig(s);
+    apr_status_t rv;
+    void *data;
+    const char *userdata_key = "ssl_scache_init";
+    struct ap_socache_hints hints;
+    
+    /* The very first invocation of this function will be the
+     * post_config invocation during server startup; do nothing for
+     * this first (and only the first) time through, since the pool
+     * will be immediately cleared anyway.  For every subsequent
+     * invocation, initialize the configured cache. */
+    apr_pool_userdata_get(&data, userdata_key, s->process->pool);
+    if (!data) {
+        apr_pool_userdata_set((const void *)1, userdata_key,
+                              apr_pool_cleanup_null, s->process->pool);
+        return;
+    }
+
+#ifdef HAVE_OCSP_STAPLING
+    if (mc->stapling_cache) {
+        memset(&hints, 0, sizeof hints);
+        hints.avg_obj_size = 1500;
+        hints.avg_id_len = 20;
+        hints.expiry_interval = 300;
+    
+        rv = mc->stapling_cache->init(mc->stapling_cache_context,
+                                     "mod_ssl-stapling", &hints, s, p);
+        if (rv) {
+            /* ABORT ABORT etc. */
+            ssl_die();
+        }
+    }
+#endif
 
     /*
      * Warn the user that he should use the session cache.
      * But we can operate without it, of course.
      */
-    if (mc->nSessionCacheMode == SSL_SCMODE_UNSET) {
+    if (mc->sesscache == NULL) {
         ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                      "Init: Session Cache is not configured "
                      "[hint: SSLSessionCache]");
-        mc->nSessionCacheMode = SSL_SCMODE_NONE;
         return;
     }
 
-    if (mc->nSessionCacheMode == SSL_SCMODE_DBM)
-        ssl_scache_dbm_init(s, p);
-#ifdef HAVE_DISTCACHE
-    else if (mc->nSessionCacheMode == SSL_SCMODE_DC)
-        ssl_scache_dc_init(s, p);
-#endif
-    else if (mc->nSessionCacheMode == SSL_SCMODE_SHMCB) {
-        void *data;
-        const char *userdata_key = "ssl_scache_init";
-
-        apr_pool_userdata_get(&data, userdata_key, s->process->pool);
-        if (!data) {
-            apr_pool_userdata_set((const void *)1, userdata_key,
-                                  apr_pool_cleanup_null, s->process->pool);
-            return;
-        }
-        ssl_scache_shmcb_init(s, p);
+    memset(&hints, 0, sizeof hints);
+    hints.avg_obj_size = 150;
+    hints.avg_id_len = 30;
+    hints.expiry_interval = 30;
+    
+    rv = mc->sesscache->init(mc->sesscache_context, "mod_ssl-session", &hints, s, p);
+    if (rv) {
+        /* ABORT ABORT etc. */
+        ssl_die();
     }
 }
 
 void ssl_scache_kill(server_rec *s)
 {
     SSLModConfigRec *mc = myModConfig(s);
+    
+    if (mc->sesscache) {
+        mc->sesscache->destroy(mc->sesscache_context, s);
+    }
 
-    if (mc->nSessionCacheMode == SSL_SCMODE_DBM)
-        ssl_scache_dbm_kill(s);
-    else if (mc->nSessionCacheMode == SSL_SCMODE_SHMCB)
-        ssl_scache_shmcb_kill(s);
-#ifdef HAVE_DISTCACHE
-    else if (mc->nSessionCacheMode == SSL_SCMODE_DC)
-        ssl_scache_dc_kill(s);
+#ifdef HAVE_OCSP_STAPLING
+    if (mc->stapling_cache) {
+        mc->stapling_cache->destroy(mc->stapling_cache_context, s);
+    }
 #endif
-    return;
+
 }
 
-BOOL ssl_scache_store(server_rec *s, UCHAR *id, int idlen, time_t expiry, SSL_SESSION *sess)
+BOOL ssl_scache_store(server_rec *s, UCHAR *id, int idlen,
+                      apr_time_t expiry, SSL_SESSION *sess,
+                      apr_pool_t *p)
 {
     SSLModConfigRec *mc = myModConfig(s);
-    BOOL rv = FALSE;
+    unsigned char encoded[SSL_SESSION_MAX_DER], *ptr;
+    unsigned int len;
+    apr_status_t rv;
+
+    /* Serialise the session. */
+    len = i2d_SSL_SESSION(sess, NULL);
+    if (len > sizeof encoded) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+                     "session is too big (%u bytes)", len);
+        return FALSE;
+    }
 
-    if (mc->nSessionCacheMode == SSL_SCMODE_DBM)
-        rv = ssl_scache_dbm_store(s, id, idlen, expiry, sess);
-    else if (mc->nSessionCacheMode == SSL_SCMODE_SHMCB)
-        rv = ssl_scache_shmcb_store(s, id, idlen, expiry, sess);
-#ifdef HAVE_DISTCACHE
-    else if (mc->nSessionCacheMode == SSL_SCMODE_DC)
-        rv = ssl_scache_dc_store(s, id, idlen, expiry, sess);
-#endif
-    return rv;
+    ptr = encoded;
+    len = i2d_SSL_SESSION(sess, &ptr);
+
+    if (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
+        ssl_mutex_on(s);
+    }
+    
+    rv = mc->sesscache->store(mc->sesscache_context, s, id, idlen, 
+                              expiry, encoded, len, p);
+
+    if (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
+        ssl_mutex_off(s);
+    }
+
+    return rv == APR_SUCCESS ? TRUE : FALSE;
 }
 
-SSL_SESSION *ssl_scache_retrieve(server_rec *s, UCHAR *id, int idlen)
+SSL_SESSION *ssl_scache_retrieve(server_rec *s, UCHAR *id, int idlen,
+                                 apr_pool_t *p)
 {
     SSLModConfigRec *mc = myModConfig(s);
-    SSL_SESSION *sess = NULL;
+    unsigned char dest[SSL_SESSION_MAX_DER];
+    unsigned int destlen = SSL_SESSION_MAX_DER;
+    MODSSL_D2I_SSL_SESSION_CONST unsigned char *ptr;
+    apr_status_t rv;
 
-    if (mc->nSessionCacheMode == SSL_SCMODE_DBM)
-        sess = ssl_scache_dbm_retrieve(s, id, idlen);
-    else if (mc->nSessionCacheMode == SSL_SCMODE_SHMCB)
-        sess = ssl_scache_shmcb_retrieve(s, id, idlen);
-#ifdef HAVE_DISTCACHE
-    else if (mc->nSessionCacheMode == SSL_SCMODE_DC)
-        sess = ssl_scache_dc_retrieve(s, id, idlen);
-#endif
-    return sess;
+    if (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
+        ssl_mutex_on(s);
+    }
+
+    rv = mc->sesscache->retrieve(mc->sesscache_context, s, id, idlen, 
+                                 dest, &destlen, p);
+
+    if (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
+        ssl_mutex_off(s);
+    }
+
+    if (rv != APR_SUCCESS) {
+        return NULL;
+    }
+
+    ptr = dest;
+
+    return d2i_SSL_SESSION(NULL, &ptr, destlen);
 }
 
-void ssl_scache_remove(server_rec *s, UCHAR *id, int idlen)
+void ssl_scache_remove(server_rec *s, UCHAR *id, int idlen,
+                       apr_pool_t *p)
 {
     SSLModConfigRec *mc = myModConfig(s);
 
-    if (mc->nSessionCacheMode == SSL_SCMODE_DBM)
-        ssl_scache_dbm_remove(s, id, idlen);
-    else if (mc->nSessionCacheMode == SSL_SCMODE_SHMCB)
-        ssl_scache_shmcb_remove(s, id, idlen);
-#ifdef HAVE_DISTCACHE
-    else if (mc->nSessionCacheMode == SSL_SCMODE_DC)
-        ssl_scache_dc_remove(s, id, idlen);
-#endif
-    return;
+    if (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
+        ssl_mutex_on(s);
+    }
+
+    mc->sesscache->remove(mc->sesscache_context, s, id, idlen, p);
+
+    if (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
+        ssl_mutex_off(s);
+    }
 }
 
 /*  _________________________________________________________________
 **
 **  SSL Extension to mod_status
 **  _________________________________________________________________
 */
 static int ssl_ext_status_hook(request_rec *r, int flags)
 {
-    SSLSrvConfigRec *sc = mySrvConfig(r->server);
+    SSLModConfigRec *mc = myModConfig(r->server);
 
-    if (sc == NULL || flags & AP_STATUS_SHORT)
+    if (mc == NULL || flags & AP_STATUS_SHORT || mc->sesscache == NULL)
         return OK;
 
     ap_rputs("<hr>\n", r);
     ap_rputs("<table cellspacing=0 cellpadding=0>\n", r);
     ap_rputs("<tr><td bgcolor=\"#000000\">\n", r);
     ap_rputs("<b><font color=\"#ffffff\" face=\"Arial,Helvetica\">SSL/TLS Session Cache Status:</font></b>\r", r);
     ap_rputs("</td></tr>\n", r);
     ap_rputs("<tr><td bgcolor=\"#ffffff\">\n", r);
 
-    if (sc->mc->nSessionCacheMode == SSL_SCMODE_DBM)
-        ssl_scache_dbm_status(r, flags, r->pool);
-    else if (sc->mc->nSessionCacheMode == SSL_SCMODE_SHMCB)
-        ssl_scache_shmcb_status(r, flags, r->pool);
-#ifdef HAVE_DISTCACHE
-    else if (sc->mc->nSessionCacheMode == SSL_SCMODE_DC)
-        ssl_scache_dc_status(r, flags, r->pool);
-#endif
+    if (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
+        ssl_mutex_on(r->server);
+    }
+
+    mc->sesscache->status(mc->sesscache_context, r, flags);
+
+    if (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
+        ssl_mutex_off(r->server);
+    }
 
     ap_rputs("</td></tr>\n", r);
     ap_rputs("</table>\n", r);
     return OK;
 }
 

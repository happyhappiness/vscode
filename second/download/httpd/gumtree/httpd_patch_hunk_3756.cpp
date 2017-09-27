 **  _________________________________________________________________
 */
 static int ssl_ext_status_hook(request_rec *r, int flags)
 {
     SSLModConfigRec *mc = myModConfig(r->server);
 
-    if (mc == NULL || flags & AP_STATUS_SHORT || mc->sesscache == NULL)
+    if (mc == NULL || mc->sesscache == NULL)
         return OK;
 
-    ap_rputs("<hr>\n", r);
-    ap_rputs("<table cellspacing=0 cellpadding=0>\n", r);
-    ap_rputs("<tr><td bgcolor=\"#000000\">\n", r);
-    ap_rputs("<b><font color=\"#ffffff\" face=\"Arial,Helvetica\">SSL/TLS Session Cache Status:</font></b>\r", r);
-    ap_rputs("</td></tr>\n", r);
-    ap_rputs("<tr><td bgcolor=\"#ffffff\">\n", r);
+    if (!(flags & AP_STATUS_SHORT)) {
+        ap_rputs("<hr>\n", r);
+        ap_rputs("<table cellspacing=0 cellpadding=0>\n", r);
+        ap_rputs("<tr><td bgcolor=\"#000000\">\n", r);
+        ap_rputs("<b><font color=\"#ffffff\" face=\"Arial,Helvetica\">SSL/TLS Session Cache Status:</font></b>\r", r);
+        ap_rputs("</td></tr>\n", r);
+        ap_rputs("<tr><td bgcolor=\"#ffffff\">\n", r);
+    }
+    else {
+        ap_rputs("TLSSessionCacheStatus\n", r);
+    }
 
     if (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
         ssl_mutex_on(r->server);
     }
 
     mc->sesscache->status(mc->sesscache_context, r, flags);
 
     if (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
         ssl_mutex_off(r->server);
     }
 
-    ap_rputs("</td></tr>\n", r);
-    ap_rputs("</table>\n", r);
+    if (!(flags & AP_STATUS_SHORT)) {
+        ap_rputs("</td></tr>\n", r);
+        ap_rputs("</table>\n", r);
+    }
+
     return OK;
 }
 
 void ssl_scache_status_register(apr_pool_t *p)
 {
     APR_OPTIONAL_HOOK(ap, status_hook, ssl_ext_status_hook, NULL, NULL,

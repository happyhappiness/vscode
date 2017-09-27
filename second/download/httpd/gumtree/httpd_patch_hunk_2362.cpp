     buffer = "";
     if (maxage) {
         buffer = apr_pstrcat(r->pool, "Max-Age=", apr_ltoa(r->pool, maxage), ";", NULL);
     }
 
     /* create RFC2109 compliant cookie */
-    rfc2109 = apr_pstrcat(r->pool, name, "=", val, ";",
-                          buffer,
-                          attrs && strlen(attrs) > 0 ?
-                          attrs : DEFAULT_ATTRS, NULL);
+    rfc2109 = apr_pstrcat(r->pool, name, "=", val, ";", buffer,
+                          attrs && *attrs ? attrs : DEFAULT_ATTRS, NULL);
     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, LOG_PREFIX
                   "user '%s' set cookie: '%s'", r->user, rfc2109);
 
     /* write the cookie to the header table(s) provided */
     va_start(vp, maxage);
     while ((t = va_arg(vp, apr_table_t *))) {

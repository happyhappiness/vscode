     apr_table_t *t;
     va_list vp;
 
     /* create RFC2109 compliant cookie */
     const char *rfc2109 = apr_pstrcat(r->pool, name, "=;Max-Age=0;",
                                 attrs ? attrs : CLEAR_ATTRS, NULL);
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, LOG_PREFIX
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00009) LOG_PREFIX
                   "user '%s' removed cookie: '%s'", r->user, rfc2109);
 
     /* write the cookie to the header table(s) provided */
     va_start(vp, attrs);
     while ((t = va_arg(vp, apr_table_t *))) {
         apr_table_addn(t, SET_COOKIE, rfc2109);

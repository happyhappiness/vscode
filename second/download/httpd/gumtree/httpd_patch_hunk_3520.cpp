     apr_table_t *t;
     va_list vp;
 
     /* create RFC2965 compliant cookie */
     const char *rfc2965 = apr_pstrcat(r->pool, name2, "=;Max-Age=0;",
                                 attrs2 ? attrs2 : CLEAR_ATTRS, NULL);
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, LOG_PREFIX
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00010) LOG_PREFIX
                   "user '%s' removed cookie2: '%s'", r->user, rfc2965);
 
     /* write the cookie to the header table(s) provided */
     va_start(vp, attrs2);
     while ((t = va_arg(vp, apr_table_t *))) {
         apr_table_addn(t, SET_COOKIE2, rfc2965);

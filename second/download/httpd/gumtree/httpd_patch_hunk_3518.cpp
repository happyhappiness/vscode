         buffer = apr_pstrcat(r->pool, "Max-Age=", apr_ltoa(r->pool, maxage), ";", NULL);
     }
 
     /* create RFC2965 compliant cookie */
     rfc2965 = apr_pstrcat(r->pool, name2, "=", val, ";", buffer,
                           attrs2 && *attrs2 ? attrs2 : DEFAULT_ATTRS, NULL);
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, LOG_PREFIX
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00008) LOG_PREFIX
                   "user '%s' set cookie2: '%s'", r->user, rfc2965);
 
     /* write the cookie to the header table(s) provided */
     va_start(vp, maxage);
     while ((t = va_arg(vp, apr_table_t *))) {
         apr_table_addn(t, SET_COOKIE2, rfc2965);

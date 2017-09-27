         else {
             prefs = conf->protocols;
         }
 
         /* Select the most preferred protocol */
         if (APLOGcdebug(c)) {
-            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, 
+            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(03156) 
                           "select protocol, proposals=%s preferences=%s configured=%s", 
                           apr_array_pstrcat(pool, proposals, ','),
                           apr_array_pstrcat(pool, prefs, ','),
                           apr_array_pstrcat(pool, conf->protocols, ','));
         }
         for (i = 0; i < proposals->nelts; ++i) {

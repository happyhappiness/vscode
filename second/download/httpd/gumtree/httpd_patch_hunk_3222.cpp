     unsigned int resp_derlen = MAX_STAPLING_DER;
 
     rv = mc->stapling_cache->retrieve(mc->stapling_cache_context, s,
                                       cinf->idx, sizeof(cinf->idx),
                                       resp_der, &resp_derlen, pool);
     if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01930)
                      "stapling_get_cached_response: cache miss");
         return TRUE;
     }
     if (resp_derlen <= 1) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01931)
                      "stapling_get_cached_response: response length invalid??");
         return TRUE;
     }
     p = resp_der;
     if (pok) {
         if (*p)

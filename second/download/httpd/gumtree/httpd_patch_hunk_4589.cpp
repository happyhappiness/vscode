 #ifdef H2_OPENSSL
     myfeats.sha256 = 1;
 #endif
 #ifdef H2_NG2_INVALID_HEADER_CB
     myfeats.inv_headers = 1;
 #endif
+#ifdef H2_NG2_LOCAL_WIN_SIZE
+    myfeats.dyn_windows = 1;
+#endif
     
     apr_pool_userdata_get(&data, mod_h2_init_key, s->process->pool);
     if ( data == NULL ) {
         ap_log_error( APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03089)
                      "initializing post config dry run");
         apr_pool_userdata_set((const void *)1, mod_h2_init_key,
                               apr_pool_cleanup_null, s->process->pool);
         return APR_SUCCESS;
     }
     
     ngh2 = nghttp2_version(0);
     ap_log_error( APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(03090)
-                 "mod_http2 (v%s, feats=%s%s%s, nghttp2 %s), initializing...",
+                 "mod_http2 (v%s, feats=%s%s%s%s, nghttp2 %s), initializing...",
                  MOD_HTTP2_VERSION, 
                  myfeats.change_prio? "CHPRIO"  : "", 
                  myfeats.sha256?      "+SHA256" : "",
                  myfeats.inv_headers? "+INVHD"  : "",
+                 myfeats.dyn_windows? "+DWINS"  : "",
                  ngh2?                ngh2->version_str : "unknown");
     
     switch (h2_conn_mpm_type()) {
         case H2_MPM_SIMPLE:
         case H2_MPM_MOTORZ:
         case H2_MPM_NETWARE:

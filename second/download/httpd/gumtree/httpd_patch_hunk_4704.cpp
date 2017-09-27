     H2_MPLX_LEAVE(m);
     return status;
 }
 
 static void register_if_needed(h2_mplx *m) 
 {
-    if (!m->is_registered && !h2_iq_empty(m->q)) {
+    if (!m->aborted && !m->is_registered && !h2_iq_empty(m->q)) {
         apr_status_t status = h2_workers_register(m->workers, m); 
         if (status == APR_SUCCESS) {
             m->is_registered = 1;
         }
         else {
             ap_log_cerror(APLOG_MARK, APLOG_ERR, status, m->c, APLOGNO(10021)

                                     ap_input_mode_t mode, apr_read_type_e block,
                                     apr_off_t readbytes)
 {
     ef_ctx_t *ctx = f->ctx;
     apr_status_t rv;
 
+    /* just get out of the way of things we don't want. */
+    if (mode != AP_MODE_READBYTES) {
+        return ap_get_brigade(f->next, bb, mode, block, readbytes);
+    }
+
     if (!ctx) {
         if ((rv = init_filter_instance(f)) != APR_SUCCESS) {
             ctx = f->ctx;
             ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, APLOGNO(01470)
                           "can't initialise input filter %s: %s",
                           f->frec->name,

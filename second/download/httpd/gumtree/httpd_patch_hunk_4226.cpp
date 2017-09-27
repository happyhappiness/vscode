     return h2_response_rcreate(from_h1->stream_id, r, headers, r->pool);
 }
 
 apr_status_t h2_response_output_filter(ap_filter_t *f, apr_bucket_brigade *bb)
 {
     h2_task *task = f->ctx;
-    h2_from_h1 *from_h1 = task->output? task->output->from_h1 : NULL;
+    h2_from_h1 *from_h1 = task->output.from_h1;
     request_rec *r = f->r;
     apr_bucket *b;
     ap_bucket_error *eb = NULL;
 
     AP_DEBUG_ASSERT(from_h1 != NULL);
     
     ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                   "h2_from_h1(%d): output_filter called", from_h1->stream_id);
     
-    if (r->header_only && task->output && from_h1->response) {
+    if (r->header_only && from_h1->response) {
         /* throw away any data after we have compiled the response */
         apr_brigade_cleanup(bb);
         return OK;
     }
     
     for (b = APR_BRIGADE_FIRST(bb);

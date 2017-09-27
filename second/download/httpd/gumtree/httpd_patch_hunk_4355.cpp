          * is still ongoing. */
         return h2_conn_pre_close(ctx, c);
     }
     return DECLINED;
 }
 
+static void check_push(request_rec *r, const char *tag)
+{
+    const h2_config *conf = h2_config_rget(r);
+    if (!r->expecting_100 
+        && conf && conf->push_list && conf->push_list->nelts > 0) {
+        int i, old_status;
+        const char *old_line;
+        ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, 
+                      "%s, early announcing %d resources for push",
+                      tag, conf->push_list->nelts);
+        for (i = 0; i < conf->push_list->nelts; ++i) {
+            h2_push_res *push = &APR_ARRAY_IDX(conf->push_list, i, h2_push_res);
+            apr_table_addn(r->headers_out, "Link", 
+                           apr_psprintf(r->pool, "<%s>; rel=preload%s", 
+                                        push->uri_ref, push->critical? "; critical" : ""));
+        }
+        old_status = r->status;
+        old_line = r->status_line;
+        r->status = 103;
+        r->status_line = "103 Early Hints";
+        ap_send_interim_response(r, 1);
+        r->status = old_status;
+        r->status_line = old_line;
+    }
+}
+
 static int h2_h2_post_read_req(request_rec *r)
 {
     /* slave connection? */
     if (r->connection->master) {
         h2_ctx *ctx = h2_ctx_rget(r);
         struct h2_task *task = h2_ctx_get_task(ctx);
         /* This hook will get called twice on internal redirects. Take care
          * that we manipulate filters only once. */
         if (task && !task->filters_set) {
             ap_filter_t *f;
+            ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r, 
+                          "h2_task(%s): adding request filters", task->id);
+
+            /* setup the correct filters to process the request for h2 */
+            ap_add_input_filter("H2_REQUEST", task, r, r->connection);
             
-            /* setup the correct output filters to process the response
-             * on the proper mod_http2 way. */
-            ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r, "adding task output filter");
-            if (task->ser_headers) {
-                ap_add_output_filter("H1_TO_H2_RESP", task, r, r->connection);
-            }
-            else {
-                /* replace the core http filter that formats response headers
-                 * in HTTP/1 with our own that collects status and headers */
-                ap_remove_output_filter_byhandle(r->output_filters, "HTTP_HEADER");
-                ap_add_output_filter("H2_RESPONSE", task, r, r->connection);
-            }
+            /* replace the core http filter that formats response headers
+             * in HTTP/1 with our own that collects status and headers */
+            ap_remove_output_filter_byhandle(r->output_filters, "HTTP_HEADER");
+            ap_add_output_filter("H2_RESPONSE", task, r, r->connection);
             
-            /* trailers processing. Incoming trailers are added to this
-             * request via our h2 input filter, outgoing trailers
-             * in a special h2 out filter. */
             for (f = r->input_filters; f; f = f->next) {
-                if (!strcmp("H2_TO_H1", f->frec->name)) {
+                if (!strcmp("H2_SLAVE_IN", f->frec->name)) {
                     f->r = r;
                     break;
                 }
             }
-            ap_add_output_filter("H2_TRAILERS", task, r, r->connection);
+            ap_add_output_filter("H2_TRAILERS_OUT", task, r, r->connection);
             task->filters_set = 1;
         }
     }
     return DECLINED;
 }
 
+static int h2_h2_late_fixups(request_rec *r)
+{
+    /* slave connection? */
+    if (r->connection->master) {
+        h2_ctx *ctx = h2_ctx_rget(r);
+        struct h2_task *task = h2_ctx_get_task(ctx);
+        if (task) {
+            /* check if we copy vs. setaside files in this location */
+            task->output.copy_files = h2_config_geti(h2_config_rget(r), 
+                                                     H2_CONF_COPY_FILES);
+            if (task->output.copy_files) {
+                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
+                              "h2_slave_out(%s): copy_files on", task->id);
+                h2_beam_on_file_beam(task->output.beam, h2_beam_no_files, NULL);
+            }
+            check_push(r, "late_fixup");
+        }
+    }
+    return DECLINED;
+}
+

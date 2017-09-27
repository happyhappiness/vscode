         if (APLOGctrace1(f->c)) {
             char buffer[1024];
             apr_size_t len = sizeof(buffer)-1;
             apr_brigade_flatten(bb, buffer, &len);
             buffer[len] = 0;
             ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
-                          "h2_task(%s): getline: %s",
+                          "h2_slave_in(%s): getline: %s",
                           task->id, buffer);
         }
     }
     else {
         /* Hmm, well. There is mode AP_MODE_EATCRLF, but we chose not
          * to support it. Seems to work. */
         ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOTIMPL, f->c,
-                      APLOGNO(02942) 
-                      "h2_task, unsupported READ mode %d", mode);
+                      APLOGNO(03472) 
+                      "h2_slave_in(%s), unsupported READ mode %d", 
+                      task->id, mode);
         status = APR_ENOTIMPL;
     }
     
     if (APLOGctrace1(f->c)) {
         apr_brigade_length(bb, 0, &bblen);
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
-                      "h2_task(%s): return %ld data bytes",
-                      task->id, (long)bblen);
+                      "h2_slave_in(%s): %ld data bytes", task->id, (long)bblen);
     }
     return status;
 }
 
-/*******************************************************************************
- * task output handling
- ******************************************************************************/
-
-static apr_status_t open_response(h2_task *task)
-{
-    h2_response *response;
-    response = h2_from_h1_get_response(task->output.from_h1);
-    if (!response) {
-        /* This happens currently when ap_die(status, r) is invoked
-         * by a read request filter. */
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, task->c, APLOGNO(03204)
-                      "h2_task(%s): write without response for %s %s %s",
-                      task->id, 
-                      task->request->method, 
-                      task->request->authority, 
-                      task->request->path);
-        task->c->aborted = 1;
-        return APR_ECONNABORTED;
-    }
-    
-    if (h2_task_logio_add_bytes_out) {
-        /* count headers as if we'd do a HTTP/1.1 serialization */
-        task->output.written = h2_util_table_bytes(response->headers, 3)+1;
-        h2_task_logio_add_bytes_out(task->c, task->output.written);
-    }
-    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, task->c, APLOGNO(03348)
-                  "h2_task(%s): open response to %s %s %s",
-                  task->id, task->request->method, 
-                  task->request->authority, 
-                  task->request->path);
-    return h2_mplx_out_open(task->mplx, task->stream_id, response);
-}
-
-static apr_status_t send_out(h2_task *task, apr_bucket_brigade* bb)
+static apr_status_t h2_filter_slave_output(ap_filter_t* filter,
+                                           apr_bucket_brigade* brigade)
 {
-    apr_off_t written, left;
+    h2_task *task = h2_ctx_cget_task(filter->c);
     apr_status_t status;
-
-    apr_brigade_length(bb, 0, &written);
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
-                  "h2_task(%s): write response body (%ld bytes)", 
-                  task->id, (long)written);
     
-    status = h2_beam_send(task->output.beam, bb, 
-                          task->blocking? APR_BLOCK_READ
-                          : APR_NONBLOCK_READ);
-    if (APR_STATUS_IS_EAGAIN(status)) {
-        apr_brigade_length(bb, 0, &left);
-        written -= left;
-        status = APR_SUCCESS;
-    }
-    if (status == APR_SUCCESS) {
-        task->output.written += written;
-        if (h2_task_logio_add_bytes_out) {
-            h2_task_logio_add_bytes_out(task->c, written);
-        }
+    ap_assert(task);
+    status = slave_out(task, filter, brigade);
+    if (status != APR_SUCCESS) {
+        h2_task_rst(task, H2_ERR_INTERNAL_ERROR);
     }
     return status;
 }
 
-/* Bring the data from the brigade (which represents the result of the
- * request_rec out filter chain) into the h2_mplx for further sending
- * on the master connection. 
- */
-static apr_status_t output_write(h2_task *task, ap_filter_t* f, 
-                                 apr_bucket_brigade* bb)
+static apr_status_t h2_filter_parse_h1(ap_filter_t* f, apr_bucket_brigade* bb)
 {
-    apr_bucket *b;
-    apr_status_t status = APR_SUCCESS;
-    int flush = 0;
-    
-    if (APR_BRIGADE_EMPTY(bb)) {
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
-                      "h2_task(%s): empty write", task->id);
-        return APR_SUCCESS;
-    }
-    
-    if (task->frozen) {
-        h2_util_bb_log(task->c, task->stream_id, APLOG_TRACE2,
-                       "frozen task output write, ignored", bb);
-        while (!APR_BRIGADE_EMPTY(bb)) {
-            b = APR_BRIGADE_FIRST(bb);
-            if (AP_BUCKET_IS_EOR(b)) {
-                APR_BUCKET_REMOVE(b);
-                task->eor = b;
-            }
-            else {
-                apr_bucket_delete(b);
-            }
-        }
-        return APR_SUCCESS;
-    }
-    
-    if (!task->output.beam) {
-        h2_beam_create(&task->output.beam, task->pool, 
-                       task->stream_id, "output", 0); 
-    }
-    
-    /* Attempt to write saved brigade first */
-    if (task->output.bb && !APR_BRIGADE_EMPTY(task->output.bb)) {
-        status = send_out(task, task->output.bb); 
-        if (status != APR_SUCCESS) {
-            return status;
-        }
-    }
+    h2_task *task = h2_ctx_cget_task(f->c);
+    apr_status_t status;
     
-    /* If there is nothing saved (anymore), try to write the brigade passed */
-    if ((!task->output.bb || APR_BRIGADE_EMPTY(task->output.bb)) 
-        && !APR_BRIGADE_EMPTY(bb)) {
-        /* check if we have a flush before the end-of-request */
-        if (!task->output.response_open) {
-            for (b = APR_BRIGADE_FIRST(bb);
-                 b != APR_BRIGADE_SENTINEL(bb);
-                 b = APR_BUCKET_NEXT(b)) {
-                if (AP_BUCKET_IS_EOR(b)) {
-                    break;
-                }
-                else if (APR_BUCKET_IS_FLUSH(b)) {
-                    flush = 1;
-                }
-            }
-        }
-
-        status = send_out(task, bb); 
-        if (status != APR_SUCCESS) {
+    ap_assert(task);
+    /* There are cases where we need to parse a serialized http/1.1 
+     * response. One example is a 100-continue answer in serialized mode
+     * or via a mod_proxy setup */
+    while (!task->output.sent_response) {
+        status = h2_from_h1_parse_response(task, f, bb);
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, f->c,
+                      "h2_task(%s): parsed response", task->id);
+        if (APR_BRIGADE_EMPTY(bb) || status != APR_SUCCESS) {
             return status;
         }
     }
     
-    /* If the passed brigade is not empty, save it before return */
-    if (!APR_BRIGADE_EMPTY(bb)) {
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, task->c, APLOGNO(03405)
-                      "h2_task(%s): could not write all, saving brigade", 
-                      task->id);
-        if (!task->output.bb) {
-            task->output.bb = apr_brigade_create(task->pool, 
-                                          task->c->bucket_alloc);
-        }
-        return ap_save_brigade(f, &task->output.bb, &bb, task->pool);
-    }
-    
-    if (!task->output.response_open 
-        && (flush || h2_beam_get_mem_used(task->output.beam) > (32*1024))) {
-        /* if we have enough buffered or we got a flush bucket, open
-        * the response now. */
-        status = open_response(task);
-        task->output.response_open = 1;
-    }
-    
-    return status;
-}
-
-static apr_status_t output_finish(h2_task *task)
-{
-    apr_status_t status = APR_SUCCESS;
-    
-    if (!task->output.response_open) {
-        status = open_response(task);
-        task->output.response_open = 1;
-    }
-    return status;
-}
-
-/*******************************************************************************
- * task slave connection filters
- ******************************************************************************/
-
-static apr_status_t h2_filter_stream_input(ap_filter_t* filter,
-                                           apr_bucket_brigade* brigade,
-                                           ap_input_mode_t mode,
-                                           apr_read_type_e block,
-                                           apr_off_t readbytes)
-{
-    h2_task *task = h2_ctx_cget_task(filter->c);
-    AP_DEBUG_ASSERT(task);
-    return input_read(task, filter, brigade, mode, block, readbytes);
-}
-
-static apr_status_t h2_filter_stream_output(ap_filter_t* filter,
-                                            apr_bucket_brigade* brigade)
-{
-    h2_task *task = h2_ctx_cget_task(filter->c);
-    AP_DEBUG_ASSERT(task);
-    return output_write(task, filter, brigade);
-}
-
-static apr_status_t h2_filter_read_response(ap_filter_t* filter,
-                                            apr_bucket_brigade* bb)
-{
-    h2_task *task = h2_ctx_cget_task(filter->c);
-    AP_DEBUG_ASSERT(task);
-    if (!task->output.from_h1) {
-        return APR_ECONNABORTED;
-    }
-    return h2_from_h1_read_response(task->output.from_h1, filter, bb);
+    return ap_pass_brigade(f->next, bb);
 }
 
 /*******************************************************************************
  * task things
  ******************************************************************************/
  
-void h2_task_set_response(h2_task *task, h2_response *response) 
-{
-    AP_DEBUG_ASSERT(response);
-    AP_DEBUG_ASSERT(!task->response);
-    /* we used to clone the response into out own pool. But
-     * we have much tighter control over the EOR bucket nowadays,
-     * so just use the instance given */
-    task->response = response;
-    if (response->rst_error) {
-        h2_task_rst(task, response->rst_error);
-    }
-}
-
-
 int h2_task_can_redo(h2_task *task) {
-    if (task->submitted
-        || (task->input.beam && h2_beam_was_received(task->input.beam)) 
-        || !task->request) {
+    if (h2_beam_was_received(task->input.beam)) {
         /* cannot repeat that. */
         return 0;
     }
     return (!strcmp("GET", task->request->method)
             || !strcmp("HEAD", task->request->method)
             || !strcmp("OPTIONS", task->request->method));
 }
 
 void h2_task_redo(h2_task *task)
 {
-    task->response = NULL;
     task->rst_error = 0;
 }
 
 void h2_task_rst(h2_task *task, int error)
 {
     task->rst_error = error;
-    if (task->input.beam) {
-        h2_beam_abort(task->input.beam);
-    }
-    if (task->output.beam) {
+    h2_beam_abort(task->input.beam);
+    if (!task->worker_done) {
         h2_beam_abort(task->output.beam);
     }
     if (task->c) {
         task->c->aborted = 1;
     }
 }

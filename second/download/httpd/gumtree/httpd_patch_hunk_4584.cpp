     request_rec *r;
 
     ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                   "h2_task(%s): create request_rec", task->id);
     r = h2_request_create_rec(req, c);
     if (r && (r->status == HTTP_OK)) {
+        /* set timeouts for virtual host of request */
+        if (task->timeout != r->server->timeout) {
+            task->timeout = r->server->timeout;
+            h2_beam_timeout_set(task->output.beam, task->timeout);
+            if (task->input.beam) {
+                h2_beam_timeout_set(task->input.beam, task->timeout);
+            }
+        }
+        
         ap_update_child_status(c->sbh, SERVER_BUSY_WRITE, r);
         
         if (cs) {
             cs->state = CONN_STATE_HANDLER;
         }
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,

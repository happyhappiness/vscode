  * on the master connection. 
  */
 apr_status_t h2_task_output_write(h2_task_output *output,
                                   ap_filter_t* f, apr_bucket_brigade* bb)
 {
     apr_status_t status;
+    
     if (APR_BRIGADE_EMPTY(bb)) {
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
-                      "h2_task_output(%s): empty write", output->env->id);
+                      "h2_task_output(%s): empty write", output->task->id);
         return APR_SUCCESS;
     }
     
     status = open_if_needed(output, f, bb);
     if (status != APR_EOF) {
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                       "h2_task_output(%s): opened and passed brigade", 
-                      output->env->id);
+                      output->task->id);
         return status;
     }
+    
     ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
-                  "h2_task_output(%s): write brigade", output->env->id);
-    return h2_mplx_out_write(output->env->mplx, output->env->stream_id, 
-                             f, bb, output->env->io);
+                  "h2_task_output(%s): write brigade", output->task->id);
+    return h2_mplx_out_write(output->task->mplx, output->task->stream_id, 
+                             f, bb, get_trailers(output), output->task->io);
 }
 

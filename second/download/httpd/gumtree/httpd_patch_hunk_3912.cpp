                                 apr_read_type_e block,
                                 apr_off_t readbytes)
 {
     apr_status_t status = APR_SUCCESS;
     apr_off_t bblen = 0;
     
-    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, f->c,
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                   "h2_task_input(%s): read, block=%d, mode=%d, readbytes=%ld", 
-                  input->env->id, block, mode, (long)readbytes);
+                  input->task->id, block, mode, (long)readbytes);
+    
+    if (mode == AP_MODE_INIT) {
+        return ap_get_brigade(f->c->input_filters, bb, mode, block, readbytes);
+    }
     
     if (is_aborted(f)) {
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
-                      "h2_task_input(%s): is aborted", 
-                      input->env->id);
+                      "h2_task_input(%s): is aborted", input->task->id);
         return APR_ECONNABORTED;
     }
     
-    if (mode == AP_MODE_INIT) {
-        return APR_SUCCESS;
-    }
-    
     if (input->bb) {
         status = apr_brigade_length(input->bb, 1, &bblen);
         if (status != APR_SUCCESS) {
             ap_log_cerror(APLOG_MARK, APLOG_WARNING, status, f->c,
                           APLOGNO(02958) "h2_task_input(%s): brigade length fail", 
-                          input->env->id);
+                          input->task->id);
             return status;
         }
     }
     
-    if ((bblen == 0) && input->env->input_eos) {
+    if ((bblen == 0) && input->task->input_eos) {
         return APR_EOF;
     }
     
     while ((bblen == 0) || (mode == AP_MODE_READBYTES && bblen < readbytes)) {
         /* Get more data for our stream from mplx.
          */
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                       "h2_task_input(%s): get more data from mplx, block=%d, "
                       "readbytes=%ld, queued=%ld",
-                      input->env->id, block, 
+                      input->task->id, block, 
                       (long)readbytes, (long)bblen);
         
         /* Although we sometimes get called with APR_NONBLOCK_READs, 
          we seem to  fill our buffer blocking. Otherwise we get EAGAIN,
          return that to our caller and everyone throws up their hands,
          never calling us again. */
-        status = h2_mplx_in_read(input->env->mplx, APR_BLOCK_READ,
-                                 input->env->stream_id, input->bb, 
-                                 input->env->io);
+        status = h2_mplx_in_read(input->task->mplx, APR_BLOCK_READ,
+                                 input->task->stream_id, input->bb, 
+                                 input->task->io);
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                       "h2_task_input(%s): mplx in read returned",
-                      input->env->id);
+                      input->task->id);
         if (status != APR_SUCCESS) {
             return status;
         }
         status = apr_brigade_length(input->bb, 1, &bblen);
         if (status != APR_SUCCESS) {
             return status;
         }
         if ((bblen == 0) && (block == APR_NONBLOCK_READ)) {
-            return h2_util_has_eos(input->bb, 0)? APR_EOF : APR_EAGAIN;
+            return h2_util_has_eos(input->bb, -1)? APR_EOF : APR_EAGAIN;
         }
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                       "h2_task_input(%s): mplx in read, %ld bytes in brigade",
-                      input->env->id, (long)bblen);
+                      input->task->id, (long)bblen);
     }
     
     ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                   "h2_task_input(%s): read, mode=%d, block=%d, "
                   "readbytes=%ld, queued=%ld",
-                  input->env->id, mode, block, 
+                  input->task->id, mode, block, 
                   (long)readbytes, (long)bblen);
            
     if (!APR_BRIGADE_EMPTY(input->bb)) {
         if (mode == AP_MODE_EXHAUSTIVE) {
             /* return all we have */
-            return h2_util_move(bb, input->bb, readbytes, 0, 
+            return h2_util_move(bb, input->bb, readbytes, NULL, 
                                 "task_input_read(exhaustive)");
         }
         else if (mode == AP_MODE_READBYTES) {
-            return h2_util_move(bb, input->bb, readbytes, 0, 
+            return h2_util_move(bb, input->bb, readbytes, NULL, 
                                 "task_input_read(readbytes)");
         }
         else if (mode == AP_MODE_SPECULATIVE) {
             /* return not more than was asked for */
             return h2_util_copy(bb, input->bb, readbytes,  
                                 "task_input_read(speculative)");

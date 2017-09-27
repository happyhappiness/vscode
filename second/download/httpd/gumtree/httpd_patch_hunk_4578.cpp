             apr_bucket_delete(b);
         } 
     }
     
     while (APR_BRIGADE_EMPTY(task->input.bb)) {
         /* Get more input data for our request. */
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
-                      "h2_slave_in(%s): get more data from mplx, block=%d, "
-                      "readbytes=%ld", task->id, block, (long)readbytes);
-        
-        /* Override the block mode we get called with depending on the input's
-         * setting. */
+        if (trace1) {
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
+                          "h2_slave_in(%s): get more data from mplx, block=%d, "
+                          "readbytes=%ld", task->id, block, (long)readbytes);
+        }
         if (task->input.beam) {
             status = h2_beam_receive(task->input.beam, task->input.bb, block, 
-                                     H2MIN(readbytes, 32*1024));
+                                     128*1024);
         }
         else {
             status = APR_EOF;
         }
         
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, f->c,
-                      "h2_slave_in(%s): read returned", task->id);
+        if (trace1) {
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, f->c,
+                          "h2_slave_in(%s): read returned", task->id);
+        }
         if (APR_STATUS_IS_EAGAIN(status) 
             && (mode == AP_MODE_GETLINE || block == APR_BLOCK_READ)) {
             /* chunked input handling does not seem to like it if we
              * return with APR_EAGAIN from a GETLINE read... 
              * upload 100k test on test-ser.example.org hangs */
             status = APR_SUCCESS;

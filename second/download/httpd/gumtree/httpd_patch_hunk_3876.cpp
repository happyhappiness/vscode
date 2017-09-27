                 break;
             }
         }
         
     }
     else {
-        status = apr_brigade_write(io->output, flush_out, io, buf, length);
-        if (status != APR_SUCCESS) {
-            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, io->connection,
-                          "h2_conn_io: write error");
-        }
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, io->connection,
+                      "h2_conn_io: writing %ld bytes to brigade", (long)length);
+        status = apr_brigade_write(io->output, pass_out, io, buf, length);
     }
     
     return status;
 }
 
+apr_status_t h2_conn_io_writeb(h2_conn_io *io, apr_bucket *b)
+{
+    APR_BRIGADE_INSERT_TAIL(io->output, b);
+    io->unflushed = 1;
+    return APR_SUCCESS;
+}
 
-apr_status_t h2_conn_io_flush(h2_conn_io *io)
+apr_status_t h2_conn_io_consider_flush(h2_conn_io *io)
 {
+    apr_status_t status = APR_SUCCESS;
+    
+    /* The HTTP/1.1 network output buffer/flush behaviour does not
+     * give optimal performance in the HTTP/2 case, as the pattern of
+     * buckets (data/eor/eos) is different.
+     * As long as we have not found out the "best" way to deal with
+     * this, force a flush at least every WRITE_BUFFER_SIZE amount
+     * of data.
+     */
     if (io->unflushed) {
-        apr_status_t status; 
+        apr_off_t len = 0;
+        if (!APR_BRIGADE_EMPTY(io->output)) {
+            apr_brigade_length(io->output, 0, &len);
+        }
+        len += io->buflen;
+        if (len >= WRITE_BUFFER_SIZE) {
+            return h2_conn_io_pass(io);
+        }
+    }
+    return status;
+}
+
+static apr_status_t h2_conn_io_flush_int(h2_conn_io *io, int force)
+{
+    if (io->unflushed || force) {
         if (io->buflen > 0) {
+            /* something in the buffer, put it in the output brigade */
             ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, io->connection,
                           "h2_conn_io: flush, flushing %ld bytes", (long)io->buflen);
             bucketeer_buffer(io);
             io->buflen = 0;
         }
-        /* Append flush.
-         */
-        APR_BRIGADE_INSERT_TAIL(io->output,
-                                apr_bucket_flush_create(io->output->bucket_alloc));
         
-        /* Send it out through installed filters (TLS) to the client */
-        status = flush_out(io->output, io);
-        
-        if (status == APR_SUCCESS) {
-            /* These are all fine and no reason for concern. Everything else
-             * is interesting. */
-            io->unflushed = 0;
-        }
-        else {
-            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, io->connection,
-                          "h2_conn_io: flush error");
+        if (force) {
+            APR_BRIGADE_INSERT_TAIL(io->output,
+                                    apr_bucket_flush_create(io->output->bucket_alloc));
         }
         
-        return status;
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, io->connection,
+                      "h2_conn_io: flush");
+        /* Send it out */
+        io->unflushed = 0;
+        return pass_out(io->output, io);
+        /* no more access after this, as we might have flushed an EOC bucket
+         * that de-allocated us all. */
     }
     return APR_SUCCESS;
 }
 
+apr_status_t h2_conn_io_flush(h2_conn_io *io)
+{
+    return h2_conn_io_flush_int(io, 1);
+}
+
+apr_status_t h2_conn_io_pass(h2_conn_io *io)
+{
+    return h2_conn_io_flush_int(io, 0);
+}
+
+apr_status_t h2_conn_io_close(h2_conn_io *io, void *session)
+{
+    apr_bucket *b;
+
+    /* Send out anything in our buffers */
+    h2_conn_io_flush_int(io, 0);
+    
+    b = h2_bucket_eoc_create(io->connection->bucket_alloc, session);
+    APR_BRIGADE_INSERT_TAIL(io->output, b);
+    b = apr_bucket_flush_create(io->connection->bucket_alloc);
+    APR_BRIGADE_INSERT_TAIL(io->output, b);
+    return ap_pass_brigade(io->connection->output_filters, io->output);
+    /* and all is gone */
+}

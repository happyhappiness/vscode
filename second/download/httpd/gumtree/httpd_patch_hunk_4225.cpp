         /* connection is hot, use max size */
         io->write_size = WRITE_SIZE_MAX;
         ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, io->c,
                       "h2_conn_io(%ld): threshold reached, write size now %ld", 
                       (long)io->c->id, (long)io->write_size);
     }
-    
-    bcount = (int)(remaining / io->write_size);
-    for (i = 0; i < bcount; ++i) {
-        b = apr_bucket_transient_create(data, io->write_size, 
-                                        io->output->bucket_alloc);
-        APR_BRIGADE_INSERT_TAIL(io->output, b);
-        data += io->write_size;
-        remaining -= io->write_size;
-    }
-    
-    if (remaining > 0) {
-        b = apr_bucket_transient_create(data, remaining, 
-                                        io->output->bucket_alloc);
-        APR_BRIGADE_INSERT_TAIL(io->output, b);
-    }
-    return APR_SUCCESS;
-}
-
-apr_status_t h2_conn_io_writeb(h2_conn_io *io, apr_bucket *b)
-{
-    APR_BRIGADE_INSERT_TAIL(io->output, b);
-    return APR_SUCCESS;
 }
 
-static apr_status_t h2_conn_io_flush_int(h2_conn_io *io, int flush, int eoc)
+static apr_status_t pass_output(h2_conn_io *io, int flush, int eoc)
 {
-    pass_out_ctx ctx;
+    conn_rec *c = io->c;
     apr_bucket *b;
+    apr_off_t bblen;
+    apr_status_t status;
     
-    if (io->buflen == 0 && APR_BRIGADE_EMPTY(io->output)) {
-        return APR_SUCCESS;
-    }
-        
-    if (io->buflen > 0) {
-        /* something in the buffer, put it in the output brigade */
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, io->c,
-                      "h2_conn_io: flush, flushing %ld bytes", 
-                      (long)io->buflen);
-        bucketeer_buffer(io);
-    }
-    
+    append_scratch(io);
     if (flush) {
-        b = apr_bucket_flush_create(io->c->bucket_alloc);
+        b = apr_bucket_flush_create(c->bucket_alloc);
         APR_BRIGADE_INSERT_TAIL(io->output, b);
     }
     
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, io->c, "h2_conn_io: flush");
-    io->buflen = 0;
-    ctx.c = io->c;
-    ctx.io = eoc? NULL : io;
+    if (APR_BRIGADE_EMPTY(io->output)) {
+        return APR_SUCCESS;
+    }
     
-    return pass_out(io->output, &ctx);
-    /* no more access after this, as we might have flushed an EOC bucket
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, c, "h2_conn_io: pass_output");
+    ap_update_child_status(c->sbh, SERVER_BUSY_WRITE, NULL);
+    apr_brigade_length(io->output, 0, &bblen);
+    
+    h2_conn_io_bb_log(c, 0, APLOG_TRACE2, "master conn pass", io->output);
+    status = ap_pass_brigade(c->output_filters, io->output);
+
+    /* careful with access after this, as we might have flushed an EOC bucket
      * that de-allocated us all. */
+    if (!eoc) {
+        apr_brigade_cleanup(io->output);
+        if (status == APR_SUCCESS) {
+            io->bytes_written += (apr_size_t)bblen;
+            io->last_write = apr_time_now();
+        }
+    }
+    
+    if (status != APR_SUCCESS) {
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, c, APLOGNO(03044)
+                      "h2_conn_io(%ld): pass_out brigade %ld bytes",
+                      c->id, (long)bblen);
+    }
+    return status;
 }
 
 apr_status_t h2_conn_io_flush(h2_conn_io *io)
 {
-    return h2_conn_io_flush_int(io, 1, 0);
-}
-
-apr_status_t h2_conn_io_consider_pass(h2_conn_io *io)
-{
-    apr_off_t len = 0;
-    
-    if (!APR_BRIGADE_EMPTY(io->output)) {
-        len = h2_brigade_mem_size(io->output);
-    }
-    len += io->buflen;
-    if (len >= WRITE_BUFFER_SIZE) {
-        return h2_conn_io_flush_int(io, 1, 0);
-    }
-    return APR_SUCCESS;
+    return pass_output(io, 1, 0);
 }
 
 apr_status_t h2_conn_io_write_eoc(h2_conn_io *io, h2_session *session)
 {
     apr_bucket *b = h2_bucket_eoc_create(io->c->bucket_alloc, session);
     APR_BRIGADE_INSERT_TAIL(io->output, b);
-    return h2_conn_io_flush_int(io, 0, 1);
+    return pass_output(io, 1, 1);
 }
 
-apr_status_t h2_conn_io_write(h2_conn_io *io, 
-                              const char *buf, size_t length)
+apr_status_t h2_conn_io_write(h2_conn_io *io, const char *data, size_t length)
 {
     apr_status_t status = APR_SUCCESS;
-    pass_out_ctx ctx;
+    apr_size_t remain;
     
-    ctx.c = io->c;
-    ctx.io = io;
-    if (io->bufsize > 0) {
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, io->c,
-                      "h2_conn_io: buffering %ld bytes", (long)length);
-                      
-        if (!APR_BRIGADE_EMPTY(io->output)) {
-            status = h2_conn_io_flush_int(io, 0, 0);
-        }
-        
-        while (length > 0 && (status == APR_SUCCESS)) {
-            apr_size_t avail = io->bufsize - io->buflen;
-            if (avail <= 0) {
-                status = h2_conn_io_flush_int(io, 0, 0);
-            }
-            else if (length > avail) {
-                memcpy(io->buffer + io->buflen, buf, avail);
-                io->buflen += avail;
-                length -= avail;
-                buf += avail;
+    if (io->buffer_output) {
+        while (length > 0) {
+            remain = assure_scratch_space(io);
+            if (remain >= length) {
+#if LOG_SCRATCH
+                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, io->c, APLOGNO(03389)
+                              "h2_conn_io(%ld): write_to_scratch(%ld)", 
+                              io->c->id, (long)length); 
+#endif
+                memcpy(io->scratch + io->slen, data, length);
+                io->slen += length;
+                length = 0;
             }
             else {
-                memcpy(io->buffer + io->buflen, buf, length);
-                io->buflen += length;
-                length = 0;
-                break;
+#if LOG_SCRATCH
+                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, io->c, APLOGNO(03390)
+                              "h2_conn_io(%ld): write_to_scratch(%ld)", 
+                              io->c->id, (long)remain); 
+#endif
+                memcpy(io->scratch + io->slen, data, remain);
+                io->slen += remain;
+                data += remain;
+                length -= remain;
             }
         }
-        
     }
     else {
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, status, io->c,
-                      "h2_conn_io: writing %ld bytes to brigade", (long)length);
-        status = apr_brigade_write(io->output, pass_out, &ctx, buf, length);
+        status = apr_brigade_write(io->output, NULL, NULL, data, length);
     }
+    return status;
+}
+
+apr_status_t h2_conn_io_pass(h2_conn_io *io, apr_bucket_brigade *bb)
+{
+    apr_bucket *b;
+    apr_status_t status = APR_SUCCESS;
     
+    check_write_size(io);
+    while (!APR_BRIGADE_EMPTY(bb) && status == APR_SUCCESS) {
+        b = APR_BRIGADE_FIRST(bb);
+        
+        if (APR_BUCKET_IS_METADATA(b)) {
+            /* need to finish any open scratch bucket, as meta data 
+             * needs to be forward "in order". */
+            append_scratch(io);
+            APR_BUCKET_REMOVE(b);
+            APR_BRIGADE_INSERT_TAIL(io->output, b);
+        }
+        else if (io->buffer_output) {
+            apr_size_t remain = assure_scratch_space(io);
+            if (b->length > remain) {
+                apr_bucket_split(b, remain);
+                if (io->slen == 0) {
+                    /* complete write_size bucket, append unchanged */
+                    APR_BUCKET_REMOVE(b);
+                    APR_BRIGADE_INSERT_TAIL(io->output, b);
+#if LOG_SCRATCH
+                    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, io->c, APLOGNO(03391)
+                                  "h2_conn_io(%ld): pass bucket(%ld)", 
+                                  io->c->id, (long)b->length);
+#endif
+                    continue;
+                }
+            }
+            else {
+                /* bucket fits in remain, copy to scratch */
+                status = read_to_scratch(io, b);
+                apr_bucket_delete(b);
+                continue;
+            }
+        }
+        else {
+            /* no buffering, forward buckets setaside on flush */
+            if (APR_BUCKET_IS_TRANSIENT(b)) {
+                apr_bucket_setaside(b, io->c->pool);
+            }
+            APR_BUCKET_REMOVE(b);
+            APR_BRIGADE_INSERT_TAIL(io->output, b);
+        }
+    }
+    
+    if (status == APR_SUCCESS) {
+        if (!APR_BRIGADE_EMPTY(io->output)) {
+            apr_off_t len = h2_brigade_mem_size(io->output);
+            if (len >= io->pass_threshold) {
+                return pass_output(io, 0, 0);
+            }
+        }
+    }
     return status;
 }
 

     }
     
     if (!stream->data_received) {
         /* last chance to manipulate response headers.
          * after this, only trailers */
         h2_proxy_stream_end_headers_out(stream);
-        stream->data_received = 1;
     }
+    stream->data_received += len;
     
     b = apr_bucket_transient_create((const char*)data, len, 
                                     stream->r->connection->bucket_alloc);
     APR_BRIGADE_INSERT_TAIL(stream->output, b);
     /* always flush after a DATA frame, as we have no other indication
      * of buffer use */
     b = apr_bucket_flush_create(stream->r->connection->bucket_alloc);
     APR_BRIGADE_INSERT_TAIL(stream->output, b);
     
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, stream->r, APLOGNO(03359)
-                  "h2_proxy_session(%s): pass response data for "
-                  "stream %d, %d bytes", session->id, stream_id, (int)len);
     status = ap_pass_brigade(stream->r->output_filters, stream->output);
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, stream->r, APLOGNO(03359)
+                  "h2_proxy_session(%s): stream=%d, response DATA %ld, %ld"
+                  " total", session->id, stream_id, (long)len,
+                  (long)stream->data_received);
     if (status != APR_SUCCESS) {
         ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c, APLOGNO(03344)
                       "h2_proxy_session(%s): passing output on stream %d", 
                       session->id, stream->id);
         nghttp2_submit_rst_stream(ngh2, NGHTTP2_FLAG_NONE,
                                   stream_id, NGHTTP2_STREAM_CLOSED);

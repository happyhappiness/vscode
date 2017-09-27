 
             /* We need to copy the output headers and treat them as input
              * headers as well.  BUT, we need to do this before we remove
              * TE, so that they are preserved accordingly for
              * ap_http_filter to know where to end.
              */
-            rp->headers_in = apr_table_copy(r->pool, r->headers_out);
+            backend->r->headers_in = apr_table_clone(backend->r->pool, r->headers_out);
             /*
              * Restore Transfer-Encoding header from response if we saved
              * one before and there is none left. We need it for the
              * ap_http_filter. See above.
              */
-            if (te && !apr_table_get(rp->headers_in, "Transfer-Encoding")) {
-                apr_table_add(rp->headers_in, "Transfer-Encoding", te);
+            if (te && !apr_table_get(backend->r->headers_in, "Transfer-Encoding")) {
+                apr_table_add(backend->r->headers_in, "Transfer-Encoding", te);
             }
 
             apr_table_unset(r->headers_out,"Transfer-Encoding");
 
-            ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, r->server,
-                         "proxy: start body send");
+            ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r, "start body send");
 
             /*
              * if we are overriding the errors, we can't put the content
              * of the page into the brigade
              */
-            if (!conf->error_override || !ap_is_HTTP_ERROR(proxy_status)) {
+            if (!dconf->error_override || !ap_is_HTTP_ERROR(proxy_status)) {
                 /* read the body, pass it to the output filters */
                 apr_read_type_e mode = APR_NONBLOCK_READ;
                 int finish = FALSE;
 
                 /* Handle the case where the error document is itself reverse
                  * proxied and was successful. We must maintain any previous
                  * error status so that an underlying error (eg HTTP_NOT_FOUND)
                  * doesn't become an HTTP_OK.
                  */
-                if (conf->error_override && !ap_is_HTTP_ERROR(proxy_status)
+                if (dconf->error_override && !ap_is_HTTP_ERROR(proxy_status)
                         && ap_is_HTTP_ERROR(original_status)) {
                     r->status = original_status;
                     r->status_line = original_status_line;
                 }
 
                 do {
                     apr_off_t readbytes;
                     apr_status_t rv;
 
-                    rv = ap_get_brigade(rp->input_filters, bb,
+                    rv = ap_get_brigade(backend->r->input_filters, bb,
                                         AP_MODE_READBYTES, mode,
                                         conf->io_buffer_size);
 
                     /* ap_get_brigade will return success with an empty brigade
                      * for a non-blocking read which would block: */
                     if (APR_STATUS_IS_EAGAIN(rv)

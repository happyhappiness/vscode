                 }
                 /* AJP13_SEND_HEADERS: process them */
                 status = ajp_parse_header(r, conf, conn->data);
                 if (status != APR_SUCCESS) {
                     backend_failed = 1;
                 }
+                else if ((r->status == 401) && psf->error_override) {
+                    const char *buf;
+                    const char *wa = "WWW-Authenticate";
+                    if ((buf = apr_table_get(r->headers_out, wa))) {
+                        apr_table_set(r->err_headers_out, wa, buf);
+                    } else {
+                        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+                                     "ap_proxy_ajp_request: origin server "
+                                     "sent 401 without WWW-Authenticate header");
+                    }
+                }
                 headers_sent = 1;
                 break;
             case CMD_AJP13_SEND_BODY_CHUNK:
                 /* AJP13_SEND_BODY_CHUNK: piece of data */
                 status = ajp_parse_data(r, conn->data, &size, &send_body_chunk_buff);
                 if (status == APR_SUCCESS) {
+                    /* If we are overriding the errors, we can't put the content
+                     * of the page into the brigade.
+                     */
+                    if (!psf->error_override || !ap_is_HTTP_ERROR(r->status)) {
                     /* AJP13_SEND_BODY_CHUNK with zero length
                      * is explicit flush message
                      */
                     if (size == 0) {
                         if (headers_sent) {
                             e = apr_bucket_flush_create(r->connection->bucket_alloc);

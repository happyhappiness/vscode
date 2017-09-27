                 status = ajp_parse_data(r, conn->data, &size, &buff);
                 if (status == APR_SUCCESS) {
                     e = apr_bucket_transient_create(buff, size,
                                                     r->connection->bucket_alloc);
                     APR_BRIGADE_INSERT_TAIL(output_brigade, e);
 
-#ifdef FLUSHING_BANDAID
-                    /*
-                     * If there is no more data available from backend side
-                     * currently, flush response to client.
-                     */
-                    if (apr_poll(conn_poll, 1, &conn_poll_fd, FLUSH_WAIT)
-                        == APR_TIMEUP) {
+                    if ( (conn->worker->flush_packets == flush_on) ||
+                         ( (conn->worker->flush_packets == flush_auto) &&
+                           (apr_poll(conn_poll, 1, &conn_poll_fd,
+                                     conn->worker->flush_wait)
+                             == APR_TIMEUP) ) ) {
                         e = apr_bucket_flush_create(r->connection->bucket_alloc);
                         APR_BRIGADE_INSERT_TAIL(output_brigade, e);
                     }
-#endif
                     apr_brigade_length(output_brigade, 0, &bb_len);
                     if (bb_len != -1)
                         conn->worker->s->read += bb_len;
                     if (ap_pass_brigade(r->output_filters,
                                         output_brigade) != APR_SUCCESS) {
                         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                       "proxy: error processing body");
                         isok = 0;
                     }
+                    data_sent = 1;
                     apr_brigade_cleanup(output_brigade);
                 }
                 else {
                     isok = 0;
                 }
                 break;

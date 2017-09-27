                         else {
                             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                  "Ignoring flush message received before headers");
                         }
                     }
                     else {
+                        apr_status_t rv;
+
                         e = apr_bucket_transient_create(send_body_chunk_buff, size,
                                                     r->connection->bucket_alloc);
                         APR_BRIGADE_INSERT_TAIL(output_brigade, e);
 
                         if ((conn->worker->flush_packets == flush_on) ||
                             ((conn->worker->flush_packets == flush_auto) &&
-                            (apr_poll(conn_poll, 1, &conn_poll_fd,
-                                      conn->worker->flush_wait)
-                                        == APR_TIMEUP) ) ) {
+                            ((rv = apr_poll(conn_poll, 1, &conn_poll_fd,
+                                             conn->worker->flush_wait))
+                                             != APR_SUCCESS) &&
+                              APR_STATUS_IS_TIMEUP(rv))) {
                             e = apr_bucket_flush_create(r->connection->bucket_alloc);
                             APR_BRIGADE_INSERT_TAIL(output_brigade, e);
                         }
                         apr_brigade_length(output_brigade, 0, &bb_len);
                         if (bb_len != -1)
                             conn->worker->s->read += bb_len;

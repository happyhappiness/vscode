                         else {
                             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                  "Ignoring flush message received before headers");
                         }
                     }
                     else {
-                        e = apr_bucket_transient_create(buff, size,
+                        e = apr_bucket_transient_create(send_body_chunk_buff, size,
                                                     r->connection->bucket_alloc);
                         APR_BRIGADE_INSERT_TAIL(output_brigade, e);
 
                         if ((conn->worker->flush_packets == flush_on) ||
                             ((conn->worker->flush_packets == flush_auto) &&
                             (apr_poll(conn_poll, 1, &conn_poll_fd,

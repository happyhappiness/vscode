             conn->worker->s->transferred += bufsiz;
         }
     }
 
     /* read the response */
     conn->data = NULL;
-    status = ajp_read_header(conn->sock, r,
+    status = ajp_read_header(conn->sock, r, maxsize,
                              (ajp_msg_t **)&(conn->data));
     if (status != APR_SUCCESS) {
         /* We had a failure: Close connection to backend */
         conn->close++;
         apr_brigade_destroy(input_brigade);
         ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,

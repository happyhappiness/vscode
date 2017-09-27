                       "got %" APR_SIZE_T_FMT " bytes of data", bufsiz);
         if (bufsiz > 0) {
             status = ajp_send_data_msg(conn->sock, msg, bufsiz);
             ajp_msg_log(r, msg, "First ajp_send_data_msg: ajp_ilink_send packet dump");
             if (status != APR_SUCCESS) {
                 /* We had a failure: Close connection to backend */
-                conn->close++;
+                conn->close = 1;
                 apr_brigade_destroy(input_brigade);
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00876)
                               "send failed to %pI (%s)",
                               conn->worker->cp->addr,
                               conn->worker->s->hostname);
                 /*

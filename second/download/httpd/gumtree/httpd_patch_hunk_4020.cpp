     
     if (access_status != HTTP_OK
         || (access_status = ap_run_post_read_request(r))) {
         /* Request check post hooks failed. An example of this would be a
          * request for a vhost where h2 is disabled --> 421.
          */
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, conn, APLOGNO()
+                      "h2_request(%d): access_status=%d, request_create failed",
+                      req->id, access_status);
         ap_die(access_status, r);
         ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
         ap_run_log_transaction(r);
         r = NULL;
         goto traceout;
     }

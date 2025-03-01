         conn->close++;
         apr_brigade_destroy(input_brigade);
         ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                      "proxy: read response failed from %pI (%s)",
                      conn->worker->cp->addr,
                      conn->worker->hostname);
+
+        /* If we had a successful cping/cpong and then a timeout
+         * we assume it is a request that cause a back-end timeout,
+         * but doesn't affect the whole worker.
+         */
+        if (APR_STATUS_IS_TIMEUP(status) && conn->worker->ping_timeout_set) {
+            return HTTP_GATEWAY_TIME_OUT;
+        }
+
         /*
          * This is only non fatal when we have not sent (parts) of a possible
          * request body so far (we do not store it and thus cannot sent it
          * again) and the method is idempotent. In this case we can dare to
          * retry it with a different worker if we are a balancer member.
          */

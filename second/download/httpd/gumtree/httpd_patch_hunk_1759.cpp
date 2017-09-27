         ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                      "proxy: AJP: request failed to %pI (%s)",
                      conn->worker->cp->addr,
                      conn->worker->hostname);
         if (status == AJP_EOVERFLOW)
             return HTTP_BAD_REQUEST;
-        else
-            return HTTP_SERVICE_UNAVAILABLE;
+        else {
+            /*
+             * This is only non fatal when the method is idempotent. In this
+             * case we can dare to retry it with a different worker if we are
+             * a balancer member.
+             */
+            if (is_idempotent(r) == METHOD_IDEMPOTENT) {
+                return HTTP_SERVICE_UNAVAILABLE;
+            }
+            return HTTP_INTERNAL_SERVER_ERROR;
+        }
     }
 
     /* allocate an AJP message to store the data of the buckets */
     bufsiz = maxsize;
     status = ajp_alloc_data_msg(r->pool, &buff, &bufsiz, &msg);
     if (status != APR_SUCCESS) {

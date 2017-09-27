              * In case the CPING / CPONG failed for the first time we might be
              * just out of luck and got a faulty backend connection, but the
              * backend might be healthy nevertheless. So ensure that the backend
              * TCP connection gets closed and try it once again.
              */
             if (status != APR_SUCCESS) {
-                backend->close++;
+                backend->close = 1;
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00897)
                               "cping/cpong failed to %pI (%s)",
                               worker->cp->addr, worker->s->hostname);
                 status = HTTP_SERVICE_UNAVAILABLE;
                 retry++;
                 continue;

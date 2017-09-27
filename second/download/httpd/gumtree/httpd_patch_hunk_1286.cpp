                     APR_BRIGADE_INSERT_TAIL(bb, e);
                 }
                 else {
                     APR_BUCKET_INSERT_BEFORE(eos, e);
                 }
                 ap_pass_brigade(r->output_filters, bb);
+                /* Mark the backend connection for closing */
+                backend->close = 1;
                 /* Need to return OK to avoid sending an error message */
                 return OK;
             }
             else if (!c->keepalives) {
                      ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                    "proxy: NOT Closing connection to client"
-                                   " although reading from backend server %s"
-                                   " failed.", backend->hostname);
+                                   " although reading from backend server %s:%d"
+                                   " failed.", backend->hostname,
+                                   backend->port);
             }
             return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                                  "Error reading from remote server");
         }
         /* XXX: Is this a real headers length send from remote? */
         backend->worker->s->read += len;

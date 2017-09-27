                     mode = APR_NONBLOCK_READ;
 
                     apr_brigade_length(bb, 0, &readbytes);
                     backend->worker->s->read += readbytes;
 #if DEBUGGING
                     {
-                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
-                                 r->server, "proxy (PID %d): readbytes: %#x",
-                                 getpid(), readbytes);
+                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01111)
+                                  "readbytes: %#x", readbytes);
                     }
 #endif
                     /* sanity check */
                     if (APR_BRIGADE_EMPTY(bb)) {
                         apr_brigade_cleanup(bb);
                         break;
                     }
 
                     /* Switch the allocator lifetime of the buckets */
-                    ap_proxy_buckets_lifetime_transform(r, bb, pass_bb);
+                    proxy_buckets_lifetime_transform(r, bb, pass_bb);
 
                     /* found the last brigade? */
-                    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(bb))) {
+                    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(pass_bb))) {
+
                         /* signal that we must leave */
                         finish = TRUE;
+
+                        /* the brigade may contain transient buckets that contain
+                         * data that lives only as long as the backend connection.
+                         * Force a setaside so these transient buckets become heap
+                         * buckets that live as long as the request.
+                         */
+                        for (e = APR_BRIGADE_FIRST(pass_bb); e
+                                != APR_BRIGADE_SENTINEL(pass_bb); e
+                                = APR_BUCKET_NEXT(e)) {
+                            apr_bucket_setaside(e, r->pool);
+                        }
+
+                        /* finally it is safe to clean up the brigade from the
+                         * connection pool, as we have forced a setaside on all
+                         * buckets.
+                         */
+                        apr_brigade_cleanup(bb);
+
+                        /* make sure we release the backend connection as soon
+                         * as we know we are done, so that the backend isn't
+                         * left waiting for a slow client to eventually
+                         * acknowledge the data.
+                         */
+                        ap_proxy_release_connection(backend->worker->s->scheme,
+                                backend, r->server);
+                        /* Ensure that the backend is not reused */
+                        *backend_ptr = NULL;
+
                     }
 
                     /* try send what we read */
                     if (ap_pass_brigade(r->output_filters, pass_bb) != APR_SUCCESS
                         || c->aborted) {
                         /* Ack! Phbtt! Die! User aborted! */
-                        backend->close = 1;  /* this causes socket close below */
+                        /* Only close backend if we haven't got all from the
+                         * backend. Furthermore if *backend_ptr is NULL it is no
+                         * longer safe to fiddle around with backend as it might
+                         * be already in use by another thread.
+                         */
+                        if (*backend_ptr) {
+                            backend->close = 1;  /* this causes socket close below */
+                        }
                         finish = TRUE;
                     }
 
                     /* make sure we always clean up after ourselves */
-                    apr_brigade_cleanup(bb);
                     apr_brigade_cleanup(pass_bb);
+                    apr_brigade_cleanup(bb);
 
                 } while (!finish);
             }
-            ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, r->server,
-                         "proxy: end body send");
+            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, "end body send");
         }
         else if (!interim_response) {
-            ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, r->server,
-                         "proxy: header only");
+            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, "header only");
+
+            /* make sure we release the backend connection as soon
+             * as we know we are done, so that the backend isn't
+             * left waiting for a slow client to eventually
+             * acknowledge the data.
+             */
+            ap_proxy_release_connection(backend->worker->s->scheme,
+                    backend, r->server);
+            *backend_ptr = NULL;
 
             /* Pass EOS bucket down the filter chain. */
             e = apr_bucket_eos_create(c->bucket_alloc);
             APR_BRIGADE_INSERT_TAIL(bb, e);
-            if (ap_pass_brigade(r->output_filters, bb) != APR_SUCCESS
-                || c->aborted) {
-                /* Ack! Phbtt! Die! User aborted! */
-                backend->close = 1;  /* this causes socket close below */
-            }
+            ap_pass_brigade(r->output_filters, bb);
 
             apr_brigade_cleanup(bb);
         }
     } while (interim_response && (interim_response < AP_MAX_INTERIM_RESPONSES));
 
     /* See define of AP_MAX_INTERIM_RESPONSES for why */
     if (interim_response >= AP_MAX_INTERIM_RESPONSES) {
         return ap_proxyerror(r, HTTP_BAD_GATEWAY,
-                             apr_psprintf(p, 
+                             apr_psprintf(p,
                              "Too many (%d) interim responses from origin server",
                              interim_response));
     }
 
     /* If our connection with the client is to be aborted, return DONE. */
     if (c->aborted || backend_broke) {

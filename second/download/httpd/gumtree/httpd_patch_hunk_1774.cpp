             rc = ap_proxygetline(tmp_bb, buffer, sizeof(buffer), rp, 0, &len);
         }
         if (len <= 0) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r,
                           "proxy: error reading status line from remote "
                           "server %s", backend->hostname);
+            /*
+             * If we are a reverse proxy request shutdown the connection
+             * WITHOUT ANY response to trigger a retry by the client
+             * if allowed (as for idempotent requests).
+             * BUT currently we should not do this if the request is the
+             * first request on a keepalive connection as browsers like
+             * seamonkey only display an empty page in this case and do
+             * not do a retry.
+             */
+            if (r->proxyreq == PROXYREQ_REVERSE && c->keepalives) {
+                apr_bucket *eos;
+
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                              "proxy: Closing connection to client because"
+                              " reading from backend server %s failed. Number"
+                              " of keepalives %i", backend->hostname, 
+                              c->keepalives);
+                ap_proxy_backend_broke(r, bb);
+                /*
+                 * Add an EOC bucket to signal the ap_http_header_filter
+                 * that it should get out of our way, BUT ensure that the
+                 * EOC bucket is inserted BEFORE an EOS bucket in bb as
+                 * some resource filters like mod_deflate pass everything
+                 * up to the EOS down the chain immediately and sent the
+                 * remainder of the brigade later (or even never). But in
+                 * this case the ap_http_header_filter does not get out of
+                 * our way soon enough.
+                 */
+                e = ap_bucket_eoc_create(c->bucket_alloc);
+                eos = APR_BRIGADE_LAST(bb);
+                while ((APR_BRIGADE_SENTINEL(bb) != eos)
+                       && !APR_BUCKET_IS_EOS(eos)) {
+                    eos = APR_BUCKET_PREV(eos);
+                }
+                if (eos == APR_BRIGADE_SENTINEL(bb)) {
+                    APR_BRIGADE_INSERT_TAIL(bb, e);
+                }
+                else {
+                    APR_BUCKET_INSERT_BEFORE(eos, e);
+                }
+                ap_pass_brigade(r->output_filters, bb);
+                /* Need to return OK to avoid sending an error message */
+                return OK;
+            }
+            else if (!c->keepalives) {
+                     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                                   "proxy: NOT Closing connection to client"
+                                   " although reading from backend server %s"
+                                   " failed.", backend->hostname);
+            }
             return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                                  "Error reading from remote server");
         }
         /* XXX: Is this a real headers length send from remote? */
         backend->worker->s->read += len;
 

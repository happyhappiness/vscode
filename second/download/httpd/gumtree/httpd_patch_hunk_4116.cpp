     r->filename = apr_pstrcat(r->pool, "proxy:", scheme, "//", host, sport,
                               "/", path, (search) ? "?" : "",
                               (search) ? search : "", NULL);
     return OK;
 }
 
-
-static apr_status_t proxy_wstunnel_transfer(request_rec *r, conn_rec *c_i, conn_rec *c_o,
-                                     apr_bucket_brigade *bb, char *name, int *sent)
-{
-    apr_status_t rv;
-#ifdef DEBUGGING
-    apr_off_t len;
-#endif
-
-    do {
-        apr_brigade_cleanup(bb);
-        rv = ap_get_brigade(c_i->input_filters, bb, AP_MODE_READBYTES,
-                            APR_NONBLOCK_READ, AP_IOBUFSIZE);
-        if (rv == APR_SUCCESS) {
-            if (c_o->aborted) {
-                return APR_EPIPE;
-            }
-            if (APR_BRIGADE_EMPTY(bb)) {
-                break;
-            }
-#ifdef DEBUGGING
-            len = -1;
-            apr_brigade_length(bb, 0, &len);
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02440)
-                          "read %" APR_OFF_T_FMT
-                          " bytes from %s", len, name);
-#endif
-            if (sent) {
-                *sent = 1;
-            }
-            rv = ap_pass_brigade(c_o->output_filters, bb);
-            if (rv == APR_SUCCESS) {
-                ap_fflush(c_o->output_filters, bb);
-            }
-            else {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02441)
-                              "error on %s - ap_pass_brigade",
-                              name);
-            }
-        } else if (!APR_STATUS_IS_EAGAIN(rv) && !APR_STATUS_IS_EOF(rv)) {
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(02442)
-                          "error on %s - ap_get_brigade",
-                          name);
-        }
-    } while (rv == APR_SUCCESS);
-
-    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, rv, r, "wstunnel_transfer complete");
-
-    if (APR_STATUS_IS_EAGAIN(rv)) {
-        rv = APR_SUCCESS;
-    }
-
-    return rv;
-}
-
 /*
  * process the request and write the response.
  */
 static int proxy_wstunnel_request(apr_pool_t *p, request_rec *r,
                                 proxy_conn_rec *conn,
                                 proxy_worker *worker,

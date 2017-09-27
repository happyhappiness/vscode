             }
         }
     }
     return 0;
 }
 
+PROXY_DECLARE(apr_status_t) ap_proxy_buckets_lifetime_transform(request_rec *r,
+                                                      apr_bucket_brigade *from,
+                                                      apr_bucket_brigade *to)
+{
+    apr_bucket *e;
+    apr_bucket *new;
+    const char *data;
+    apr_size_t bytes;
+    apr_status_t rv = APR_SUCCESS;
+    apr_bucket_alloc_t *bucket_alloc = to->bucket_alloc;
+
+    apr_brigade_cleanup(to);
+    for (e = APR_BRIGADE_FIRST(from);
+         e != APR_BRIGADE_SENTINEL(from);
+         e = APR_BUCKET_NEXT(e)) {
+        if (!APR_BUCKET_IS_METADATA(e)) {
+            apr_bucket_read(e, &data, &bytes, APR_BLOCK_READ);
+            new = apr_bucket_transient_create(data, bytes, bucket_alloc);
+            APR_BRIGADE_INSERT_TAIL(to, new);
+        }
+        else if (APR_BUCKET_IS_FLUSH(e)) {
+            new = apr_bucket_flush_create(bucket_alloc);
+            APR_BRIGADE_INSERT_TAIL(to, new);
+        }
+        else if (APR_BUCKET_IS_EOS(e)) {
+            new = apr_bucket_eos_create(bucket_alloc);
+            APR_BRIGADE_INSERT_TAIL(to, new);
+        }
+        else {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(03304)
+                          "Unhandled bucket type of type %s in"
+                          " ap_proxy_buckets_lifetime_transform", e->type->name);
+            rv = APR_EGENERAL;
+        }
+    }
+    return rv;
+}
+
+PROXY_DECLARE(apr_status_t) ap_proxy_transfer_between_connections(
+                                                       request_rec *r,
+                                                       conn_rec *c_i,
+                                                       conn_rec *c_o,
+                                                       apr_bucket_brigade *bb_i,
+                                                       apr_bucket_brigade *bb_o,
+                                                       const char *name,
+                                                       int *sent,
+                                                       apr_off_t bsize,
+                                                       int after)
+{
+    apr_status_t rv;
+#ifdef DEBUGGING
+    apr_off_t len;
+#endif
+
+    do {
+        apr_brigade_cleanup(bb_i);
+        rv = ap_get_brigade(c_i->input_filters, bb_i, AP_MODE_READBYTES,
+                            APR_NONBLOCK_READ, bsize);
+        if (rv == APR_SUCCESS) {
+            if (c_o->aborted) {
+                return APR_EPIPE;
+            }
+            if (APR_BRIGADE_EMPTY(bb_i)) {
+                break;
+            }
+#ifdef DEBUGGING
+            len = -1;
+            apr_brigade_length(bb_i, 0, &len);
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03306)
+                          "ap_proxy_transfer_between_connections: "
+                          "read %" APR_OFF_T_FMT
+                          " bytes from %s", len, name);
+#endif
+            if (sent) {
+                *sent = 1;
+            }
+            ap_proxy_buckets_lifetime_transform(r, bb_i, bb_o);
+            if (!after) {
+                apr_bucket *b;
+
+                /*
+                 * Do not use ap_fflush here since this would cause the flush
+                 * bucket to be sent in a separate brigade afterwards which
+                 * causes some filters to set aside the buckets from the first
+                 * brigade and process them when the flush arrives in the second
+                 * brigade. As set asides of our transformed buckets involve
+                 * memory copying we try to avoid this. If we have the flush
+                 * bucket in the first brigade they directly process the
+                 * buckets without setting them aside.
+                 */
+                b = apr_bucket_flush_create(bb_o->bucket_alloc);
+                APR_BRIGADE_INSERT_TAIL(bb_o, b);
+            }
+            rv = ap_pass_brigade(c_o->output_filters, bb_o);
+            if (rv != APR_SUCCESS) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(03307)
+                              "ap_proxy_transfer_between_connections: "
+                              "error on %s - ap_pass_brigade",
+                              name);
+            }
+        } else if (!APR_STATUS_IS_EAGAIN(rv) && !APR_STATUS_IS_EOF(rv)) {
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(03308)
+                          "ap_proxy_transfer_between_connections: "
+                          "error on %s - ap_get_brigade",
+                          name);
+        }
+    } while (rv == APR_SUCCESS);
+
+    if (after) {
+        ap_fflush(c_o->output_filters, bb_o);
+    }
+
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, rv, r,
+                  "ap_proxy_transfer_between_connections complete");
+
+    if (APR_STATUS_IS_EAGAIN(rv)) {
+        rv = APR_SUCCESS;
+    }
+
+    return rv;
+}
+
 void proxy_util_register_hooks(apr_pool_t *p)
 {
     APR_REGISTER_OPTIONAL_FN(ap_proxy_retry_worker);
     APR_REGISTER_OPTIONAL_FN(ap_proxy_clear_connection);
 }

         }
         return next->frec->filter_func.out_func(next, bb);
     }
     return AP_NOBODY_WROTE;
 }
 
+/* Pass the buckets to the next filter in the filter stack
+ * checking return status for filter errors.
+ * returns: OK if ap_pass_brigade returns APR_SUCCESS
+ *          AP_FILTER_ERROR if filter error exists
+ *          HTTP_INTERNAL_SERVER_ERROR for all other cases
+ *          logged with optional errmsg
+ */
+AP_DECLARE(apr_status_t) ap_pass_brigade_fchk(request_rec *r,
+                                              apr_bucket_brigade *bb,
+                                              const char *fmt,
+                                              ...)
+{
+    apr_status_t rv;
+
+    rv = ap_pass_brigade(r->output_filters, bb);
+    if (rv != APR_SUCCESS) {
+        if (rv != AP_FILTER_ERROR) {
+            if (!fmt)
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(00083)
+                              "ap_pass_brigade returned %d", rv);
+            else {
+                va_list ap;
+                const char *res;
+                va_start(ap, fmt);
+                res = apr_pvsprintf(r->pool, fmt, ap);
+                va_end(ap);
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, "%s", res);
+            }
+            return HTTP_INTERNAL_SERVER_ERROR;
+        }
+        return AP_FILTER_ERROR;
+    }
+    return OK;
+}
+
 AP_DECLARE(apr_status_t) ap_save_brigade(ap_filter_t *f,
                                          apr_bucket_brigade **saveto,
                                          apr_bucket_brigade **b, apr_pool_t *p)
 {
     apr_bucket *e;
     apr_status_t rv, srv = APR_SUCCESS;

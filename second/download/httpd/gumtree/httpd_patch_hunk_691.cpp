             if (eos) {
                 /* should not occur, because we have an APR timeout in place */
                 AP_DEBUG_ASSERT(1 != 1);
             }
             return APR_SUCCESS;
         }
-        
+
         if (rv == APR_SUCCESS) {
-            bb = apr_brigade_create(r->pool, c->bucket_alloc);
-            b = apr_bucket_transient_create(buf, len, c->bucket_alloc);
+            b = apr_bucket_heap_create(buf, len, NULL, c->bucket_alloc);
             APR_BRIGADE_INSERT_TAIL(bb, b);
-            if ((rv = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                              "ap_pass_brigade(filtered buffer) failed");
-                return rv;
-            }
         }
     } while (rv == APR_SUCCESS);
 
     if (!APR_STATUS_IS_EOF(rv)) {
         return rv;
     }
 
     if (eos) {
-        /* pass down eos */
-        bb = apr_brigade_create(r->pool, c->bucket_alloc);
         b = apr_bucket_eos_create(c->bucket_alloc);
         APR_BRIGADE_INSERT_TAIL(bb, b);
-        if ((rv = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                          "ap_pass_brigade(eos) failed");
+    }
+
+    return APR_SUCCESS;
+}
+
+static apr_status_t ef_output_filter(ap_filter_t *f, apr_bucket_brigade *bb)
+{
+    request_rec *r = f->r;
+    ef_ctx_t *ctx = f->ctx;
+    apr_status_t rv;
+
+    if (!ctx) {
+        if ((rv = init_filter_instance(f)) != APR_SUCCESS) {
             return rv;
         }
+        ctx = f->ctx;
+    }
+    if (ctx->noop) {
+        ap_remove_output_filter(f);
+        return ap_pass_brigade(f->next, bb);
     }
 
-    return APR_SUCCESS;
+    rv = ef_unified_filter(f, bb);
+    if (rv != APR_SUCCESS) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+                      "ef_unified_filter() failed");
+    }
+
+    if ((rv = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+                      "ap_pass_brigade() failed");
+    }
+    return rv;
 }
 
-#if 0
-static int ef_input_filter(ap_filter_t *f, apr_bucket_brigade *bb, 
+static int ef_input_filter(ap_filter_t *f, apr_bucket_brigade *bb,
                            ap_input_mode_t mode, apr_read_type_e block,
                            apr_off_t readbytes)
 {
+    ef_ctx_t *ctx = f->ctx;
     apr_status_t rv;
-    apr_bucket *b;
-    char *buf;
-    apr_ssize_t len;
-    char *zero;
+
+    if (!ctx) {
+        if ((rv = init_filter_instance(f)) != APR_SUCCESS) {
+            return rv;
+        }
+        ctx = f->ctx;
+    }
+
+    if (ctx->noop) {
+        ap_remove_input_filter(f);
+        return ap_get_brigade(f->next, bb, mode, block, readbytes);
+    }
 
     rv = ap_get_brigade(f->next, bb, mode, block, readbytes);
     if (rv != APR_SUCCESS) {
         return rv;
     }
 
-    APR_BRIGADE_FOREACH(b, bb) {
-        if (!APR_BUCKET_IS_EOS(b)) {
-            if ((rv = apr_bucket_read(b, (const char **)&buf, &len, APR_BLOCK_READ)) != APR_SUCCESS) {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, "apr_bucket_read() failed");
-                return rv;
-            }
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, "apr_bucket_read -> %d bytes",
-                         len);
-            while ((zero = memchr(buf, '0', len))) {
-                *zero = 'a';
-            }
-        }
-        else
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, "got eos bucket");
-    }
-
+    rv = ef_unified_filter(f, bb);
     return rv;
 }
-#endif
 
 module AP_MODULE_DECLARE_DATA ext_filter_module =
 {
     STANDARD20_MODULE_STUFF,
     create_ef_dir_conf,
     merge_ef_dir_conf,

     if (status == APR_SUCCESS && !*peos && !*plen) {
         return APR_EAGAIN;
     }
     return status;
 }
 
-void h2_util_bb_log(conn_rec *c, int stream_id, int level, 
-                    const char *tag, apr_bucket_brigade *bb)
+apr_size_t h2_util_bucket_print(char *buffer, apr_size_t bmax, 
+                                apr_bucket *b, const char *sep)
 {
-    char buffer[16 * 1024];
-    const char *line = "(null)";
-    apr_size_t bmax = sizeof(buffer)/sizeof(buffer[0]);
-    int off = 0;
-    apr_bucket *b;
+    apr_size_t off = 0;
+    if (sep && *sep) {
+        off += apr_snprintf(buffer+off, bmax-off, "%s", sep);
+    }
     
-    if (bb) {
-        memset(buffer, 0, bmax--);
-        for (b = APR_BRIGADE_FIRST(bb); 
-             bmax && (b != APR_BRIGADE_SENTINEL(bb));
-             b = APR_BUCKET_NEXT(b)) {
-            
-            if (APR_BUCKET_IS_METADATA(b)) {
-                if (APR_BUCKET_IS_EOS(b)) {
-                    off += apr_snprintf(buffer+off, bmax-off, "eos ");
-                }
-                else if (APR_BUCKET_IS_FLUSH(b)) {
-                    off += apr_snprintf(buffer+off, bmax-off, "flush ");
-                }
-                else if (AP_BUCKET_IS_EOR(b)) {
-                    off += apr_snprintf(buffer+off, bmax-off, "eor ");
-                }
-                else {
-                    off += apr_snprintf(buffer+off, bmax-off, "meta(unknown) ");
-                }
-            }
-            else {
-                const char *btype = "data";
-                if (APR_BUCKET_IS_FILE(b)) {
-                    btype = "file";
-                }
-                else if (APR_BUCKET_IS_PIPE(b)) {
-                    btype = "pipe";
-                }
-                else if (APR_BUCKET_IS_SOCKET(b)) {
-                    btype = "socket";
-                }
-                else if (APR_BUCKET_IS_HEAP(b)) {
-                    btype = "heap";
-                }
-                else if (APR_BUCKET_IS_TRANSIENT(b)) {
-                    btype = "transient";
-                }
-                else if (APR_BUCKET_IS_IMMORTAL(b)) {
-                    btype = "immortal";
-                }
-#if APR_HAS_MMAP
-                else if (APR_BUCKET_IS_MMAP(b)) {
-                    btype = "mmap";
-                }
-#endif
-                else if (APR_BUCKET_IS_POOL(b)) {
-                    btype = "pool";
-                }
-                
-                off += apr_snprintf(buffer+off, bmax-off, "%s[%ld] ", 
-                                    btype, 
-                                    (long)(b->length == ((apr_size_t)-1)? 
-                                           -1 : b->length));
-            }
+    if (APR_BUCKET_IS_METADATA(b)) {
+        if (APR_BUCKET_IS_EOS(b)) {
+            off += apr_snprintf(buffer+off, bmax-off, "eos");
+        }
+        else if (APR_BUCKET_IS_FLUSH(b)) {
+            off += apr_snprintf(buffer+off, bmax-off, "flush");
+        }
+        else if (AP_BUCKET_IS_EOR(b)) {
+            off += apr_snprintf(buffer+off, bmax-off, "eor");
+        }
+        else {
+            off += apr_snprintf(buffer+off, bmax-off, "meta(unknown)");
         }
-        line = *buffer? buffer : "(empty)";
     }
-    /* Intentional no APLOGNO */
-    ap_log_cerror(APLOG_MARK, level, 0, c, "bb_dump(%ld-%d)-%s: %s", 
-                  c->id, stream_id, tag, line);
-
-}
-
-apr_status_t h2_ltransfer_brigade(apr_bucket_brigade *to,
-                                 apr_bucket_brigade *from, 
-                                 apr_pool_t *p,
-                                 apr_off_t *plen,
-                                 int *peos)
-{
-    apr_bucket *e;
-    apr_off_t len = 0, remain = *plen;
-    apr_status_t rv;
-
-    *peos = 0;
-    
-    while (!APR_BRIGADE_EMPTY(from)) {
-        e = APR_BRIGADE_FIRST(from);
-        
-        if (APR_BUCKET_IS_METADATA(e)) {
-            if (APR_BUCKET_IS_EOS(e)) {
-                *peos = 1;
-            }
+    else {
+        const char *btype = "data";
+        if (APR_BUCKET_IS_FILE(b)) {
+            btype = "file";
         }
-        else {        
-            if (remain > 0 && e->length == ((apr_size_t)-1)) {
-                const char *ign;
-                apr_size_t ilen;
-                rv = apr_bucket_read(e, &ign, &ilen, APR_BLOCK_READ);
-                if (rv != APR_SUCCESS) {
-                    return rv;
-                }
-            }
-            
-            if (remain < e->length) {
-                if (remain <= 0) {
-                    return APR_SUCCESS;
-                }
-                apr_bucket_split(e, remain);
-            }
+        else if (APR_BUCKET_IS_PIPE(b)) {
+            btype = "pipe";
         }
-        
-        rv = apr_bucket_setaside(e, p);
-        
-        /* If the bucket type does not implement setaside, then
-         * (hopefully) morph it into a bucket type which does, and set
-         * *that* aside... */
-        if (rv == APR_ENOTIMPL) {
-            const char *s;
-            apr_size_t n;
-            
-            rv = apr_bucket_read(e, &s, &n, APR_BLOCK_READ);
-            if (rv == APR_SUCCESS) {
-                rv = apr_bucket_setaside(e, p);
-            }
+        else if (APR_BUCKET_IS_SOCKET(b)) {
+            btype = "socket";
         }
-        
-        if (rv != APR_SUCCESS) {
-            /* Return an error but still save the brigade if
-             * ->setaside() is really not implemented. */
-            if (rv != APR_ENOTIMPL) {
-                return rv;
-            }
+        else if (APR_BUCKET_IS_HEAP(b)) {
+            btype = "heap";
+        }
+        else if (APR_BUCKET_IS_TRANSIENT(b)) {
+            btype = "transient";
+        }
+        else if (APR_BUCKET_IS_IMMORTAL(b)) {
+            btype = "immortal";
+        }
+#if APR_HAS_MMAP
+        else if (APR_BUCKET_IS_MMAP(b)) {
+            btype = "mmap";
+        }
+#endif
+        else if (APR_BUCKET_IS_POOL(b)) {
+            btype = "pool";
         }
         
-        APR_BUCKET_REMOVE(e);
-        APR_BRIGADE_INSERT_TAIL(to, e);
-        len += e->length;
-        remain -= e->length;
+        off += apr_snprintf(buffer+off, bmax-off, "%s[%ld]", 
+                            btype, 
+                            (long)(b->length == ((apr_size_t)-1)? 
+                                   -1 : b->length));
     }
-    
-    *plen = len;
-    return APR_SUCCESS;
+    return off;
 }
 
-apr_status_t h2_transfer_brigade(apr_bucket_brigade *to,
-                                 apr_bucket_brigade *from, 
-                                 apr_pool_t *p)
+apr_size_t h2_util_bb_print(char *buffer, apr_size_t bmax, 
+                            const char *tag, const char *sep, 
+                            apr_bucket_brigade *bb)
 {
-    apr_bucket *e;
-    apr_status_t rv;
-
-    while (!APR_BRIGADE_EMPTY(from)) {
-        e = APR_BRIGADE_FIRST(from);
-        
-        rv = apr_bucket_setaside(e, p);
-        
-        /* If the bucket type does not implement setaside, then
-         * (hopefully) morph it into a bucket type which does, and set
-         * *that* aside... */
-        if (rv == APR_ENOTIMPL) {
-            const char *s;
-            apr_size_t n;
+    apr_size_t off = 0;
+    const char *sp = "";
+    apr_bucket *b;
+    
+    if (bb) {
+        memset(buffer, 0, bmax--);
+        off += apr_snprintf(buffer+off, bmax-off, "%s(", tag);
+        for (b = APR_BRIGADE_FIRST(bb); 
+             bmax && (b != APR_BRIGADE_SENTINEL(bb));
+             b = APR_BUCKET_NEXT(b)) {
             
-            rv = apr_bucket_read(e, &s, &n, APR_BLOCK_READ);
-            if (rv == APR_SUCCESS) {
-                rv = apr_bucket_setaside(e, p);
-            }
+            off += h2_util_bucket_print(buffer+off, bmax-off, b, sp);
+            sp = " ";
         }
-        
-        if (rv != APR_SUCCESS) {
-            /* Return an error but still save the brigade if
-             * ->setaside() is really not implemented. */
-            if (rv != APR_ENOTIMPL) {
-                return rv;
-            }
-        }
-        
-        APR_BUCKET_REMOVE(e);
-        APR_BRIGADE_INSERT_TAIL(to, e);
+        off += apr_snprintf(buffer+off, bmax-off, ")%s", sep);
     }
-    return APR_SUCCESS;
+    else {
+        off += apr_snprintf(buffer+off, bmax-off, "%s(null)%s", tag, sep);
+    }
+    return off;
 }
 
 apr_status_t h2_append_brigade(apr_bucket_brigade *to,
                                apr_bucket_brigade *from, 
                                apr_off_t *plen,
                                int *peos)

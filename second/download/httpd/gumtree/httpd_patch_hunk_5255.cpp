             APR_BRIGADE_INSERT_TAIL(ctx->bb, e);
             continue;
         }
 
         /* read */
         apr_bucket_read(e, &data, &len, APR_BLOCK_READ);
+        if (!len) {
+            apr_bucket_delete(e);
+            continue;
+        }
+        if (len > INT_MAX) {
+            apr_bucket_split(e, INT_MAX);
+            apr_bucket_read(e, &data, &len, APR_BLOCK_READ);
+        }
 
         /* first bucket contains zlib header */
-        if (!ctx->inflate_init) {
-            ctx->inflate_init = 1;
-            if (len < 10) {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01403)
-                              "Insufficient data for inflate");
-                return APR_EGENERAL;
-            }
-            else  {
-                zlib_method = data[2];
-                zlib_flags = data[3];
+        if (ctx->header_len < sizeof(ctx->header)) {
+            apr_size_t rem;
+
+            rem = sizeof(ctx->header) - ctx->header_len;
+            if (len < rem) {
+                memcpy(ctx->header + ctx->header_len, data, len);
+                ctx->header_len += len;
+                apr_bucket_delete(e);
+                continue;
+            }
+            memcpy(ctx->header + ctx->header_len, data, rem);
+            ctx->header_len += rem;
+            {
+                int zlib_method;
+                zlib_method = ctx->header[2];
                 if (zlib_method != Z_DEFLATED) {
                     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01404)
                                   "inflate: data not deflated!");
                     ap_remove_output_filter(f);
                     return ap_pass_brigade(f->next, bb);
                 }
-                if (data[0] != deflate_magic[0] ||
-                    data[1] != deflate_magic[1] ||
-                    (zlib_flags & RESERVED) != 0) {
+                if (ctx->header[0] != deflate_magic[0] ||
+                    ctx->header[1] != deflate_magic[1]) {
                         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01405)
                                       "inflate: bad header");
                     return APR_EGENERAL ;
                 }
-                data += 10 ;
-                len -= 10 ;
-           }
-           if (zlib_flags & EXTRA_FIELD) {
-               unsigned int bytes = (unsigned int)(data[0]);
-               bytes += ((unsigned int)(data[1])) << 8;
-               bytes += 2;
-               if (len < bytes) {
-                   ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01406)
-                                 "inflate: extra field too big (not "
-                                 "supported)");
-                   return APR_EGENERAL;
-               }
-               data += bytes;
-               len -= bytes;
-           }
-           if (zlib_flags & ORIG_NAME) {
-               while (len-- && *data++);
-           }
-           if (zlib_flags & COMMENT) {
-               while (len-- && *data++);
-           }
-           if (zlib_flags & HEAD_CRC) {
-                len -= 2;
-                data += 2;
-           }
+                ctx->zlib_flags = ctx->header[3];
+                if ((ctx->zlib_flags & RESERVED)) {
+                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02620)
+                                  "inflate: bad flags %02x",
+                                  ctx->zlib_flags);
+                    return APR_EGENERAL;
+                }
+            }
+            if (len == rem) {
+                apr_bucket_delete(e);
+                continue;
+            }
+            data += rem;
+            len -= rem;
+        }
+
+        if (ctx->zlib_flags) {
+            rv = consume_zlib_flags(ctx, &data, &len);
+            if (rv == APR_SUCCESS) {
+                ctx->zlib_flags = 0;
+            }
+            if (!len) {
+                apr_bucket_delete(e);
+                continue;
+            }
         }
 
         /* pass through zlib inflate. */
         ctx->stream.next_in = (unsigned char *)data;
         ctx->stream.avail_in = len;
 

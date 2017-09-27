             }
         }
 
 
         if ((status = apr_file_open(&fd, r->filename, APR_READ | APR_BINARY
 #if APR_HAS_SENDFILE
-                            | ((d->enable_sendfile == ENABLE_SENDFILE_OFF) 
+                            | ((d->enable_sendfile == ENABLE_SENDFILE_OFF)
                                                 ? 0 : APR_SENDFILE_ENABLED)
 #endif
                                     , 0, r->pool)) != APR_SUCCESS) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                           "file permissions deny server access: %s", r->filename);
             return HTTP_FORBIDDEN;
         }
 
         ap_update_mtime(r, r->finfo.mtime);
         ap_set_last_modified(r);
         ap_set_etag(r);
-        ap_set_accept_ranges(r);
+        apr_table_setn(r->headers_out, "Accept-Ranges", "bytes");
         ap_set_content_length(r, r->finfo.size);
-        if ((errstatus = ap_meets_conditions(r)) != OK) {
-            apr_file_close(fd);
-            return errstatus;
-        }
-
-        if (bld_content_md5) {
-            apr_table_setn(r->headers_out, "Content-MD5",
-                           ap_md5digest(r->pool, fd));
-        }
 
         bb = apr_brigade_create(r->pool, c->bucket_alloc);
 
-        /* For platforms where the size of the file may be larger than
-         * that which can be stored in a single bucket (whether the
-         * length field is an apr_size_t), split it into several
-         * buckets */
-        if (sizeof(apr_off_t) > sizeof(apr_size_t) 
-            && r->finfo.size > AP_MAX_SENDFILE) {
-            apr_off_t fsize = r->finfo.size;
-            e = apr_bucket_file_create(fd, 0, AP_MAX_SENDFILE, r->pool,
-                                       c->bucket_alloc);
-            while (fsize > AP_MAX_SENDFILE) {
-                apr_bucket *ce;
-                apr_bucket_copy(e, &ce);
-                APR_BRIGADE_INSERT_TAIL(bb, ce);
-                e->start += AP_MAX_SENDFILE;
-                fsize -= AP_MAX_SENDFILE;
-            }
-            e->length = (apr_size_t)fsize; /* Resize just the last bucket */
+        if ((errstatus = ap_meets_conditions(r)) != OK) {
+            apr_file_close(fd);
+            r->status = errstatus;
         }
-        else
-            e = apr_bucket_file_create(fd, 0, (apr_size_t)r->finfo.size,
-                                       r->pool, c->bucket_alloc);
+        else {
+            if (bld_content_md5) {
+                apr_table_setn(r->headers_out, "Content-MD5",
+                               ap_md5digest(r->pool, fd));
+            }
+
+            /* For platforms where the size of the file may be larger than
+             * that which can be stored in a single bucket (where the
+             * length field is an apr_size_t), split it into several
+             * buckets: */
+            if (sizeof(apr_off_t) > sizeof(apr_size_t)
+                && r->finfo.size > AP_MAX_SENDFILE) {
+                apr_off_t fsize = r->finfo.size;
+                e = apr_bucket_file_create(fd, 0, AP_MAX_SENDFILE, r->pool,
+                                           c->bucket_alloc);
+                while (fsize > AP_MAX_SENDFILE) {
+                    apr_bucket *ce;
+                    apr_bucket_copy(e, &ce);
+                    APR_BRIGADE_INSERT_TAIL(bb, ce);
+                    e->start += AP_MAX_SENDFILE;
+                    fsize -= AP_MAX_SENDFILE;
+                }
+                e->length = (apr_size_t)fsize; /* Resize just the last bucket */
+            }
+            else {
+                e = apr_bucket_file_create(fd, 0, (apr_size_t)r->finfo.size,
+                                           r->pool, c->bucket_alloc);
+            }
 
 #if APR_HAS_MMAP
-        if (d->enable_mmap == ENABLE_MMAP_OFF) {
-            (void)apr_bucket_file_enable_mmap(e, 0);
-        }
+            if (d->enable_mmap == ENABLE_MMAP_OFF) {
+                (void)apr_bucket_file_enable_mmap(e, 0);
+            }
 #endif
-        APR_BRIGADE_INSERT_TAIL(bb, e);
+            APR_BRIGADE_INSERT_TAIL(bb, e);
+        }
+
         e = apr_bucket_eos_create(c->bucket_alloc);
         APR_BRIGADE_INSERT_TAIL(bb, e);
 
-        status = ap_pass_brigade(r->output_filters, bb);
-        if (status == APR_SUCCESS
-            || r->status != HTTP_OK
-            || c->aborted) {
-            return OK; /* r->status will be respected */
-        }
-        else {
-            /* no way to know what type of error occurred */
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r,
-                          "default_handler: ap_pass_brigade returned %i",
-                          status);
-            return HTTP_INTERNAL_SERVER_ERROR;
-        }
+        return ap_pass_brigade(r->output_filters, bb);
     }
     else {              /* unusual method (not GET or POST) */
         if (r->method_number == M_INVALID) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                           "Invalid method in request %s", r->the_request);
             return HTTP_NOT_IMPLEMENTED;

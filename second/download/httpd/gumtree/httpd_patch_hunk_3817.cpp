         return APR_SUCCESS;
     }
 
     sk = sk_X509_INFO_new_null();
 
     if (pkp->cert_file) {
-        SSL_X509_INFO_load_file(ptemp, sk, pkp->cert_file);
+        load_x509_info(ptemp, sk, pkp->cert_file);
     }
 
     if (pkp->cert_path) {
-        SSL_X509_INFO_load_path(ptemp, sk, pkp->cert_path);
+        apr_dir_t *dir;
+        apr_finfo_t dirent;
+        apr_int32_t finfo_flags = APR_FINFO_TYPE|APR_FINFO_NAME;
+    
+        if (apr_dir_open(&dir, pkp->cert_path, ptemp) == APR_SUCCESS) {
+            while ((apr_dir_read(&dirent, finfo_flags, dir)) == APR_SUCCESS) {
+                const char *fullname;
+
+                if (dirent.filetype == APR_DIR) {
+                    continue; /* don't try to load directories */
+                }
+        
+                fullname = apr_pstrcat(ptemp,
+                                       pkp->cert_path, "/", dirent.name,
+                                       NULL);
+                load_x509_info(ptemp, sk, fullname);
+            }
+
+            apr_dir_close(dir);
+        }
     }
 
     if ((ncerts = sk_X509_INFO_num(sk)) <= 0) {
         sk_X509_INFO_free(sk);
         ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(02206)
                      "no client certs found for SSL proxy");

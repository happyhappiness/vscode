         rv = apr_shm_attach(&shm, fname, gpool);
     }
     else {
         rv = APR_EINVAL;
     }
     if (rv == APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02598)
+                     "apr_shm_attach() succeeded");
+
         /* check size */
         if (apr_shm_size_get(shm) != size) {
             apr_shm_detach(shm);
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(02599)
+                         "existing shared memory for %s could not be used (failed size check)",
+                         fname);
             return APR_EINVAL;
         }
         ptr = (char *)apr_shm_baseaddr_get(shm);
         memcpy(&desc, ptr, sizeof(desc));
         if (desc.size != item_size || desc.num != item_num) {
             apr_shm_detach(shm);
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(02600)
+                         "existing shared memory for %s could not be used (failed contents check)",
+                         fname);
             return APR_EINVAL;
         }
         ptr += AP_SLOTMEM_OFFSET;
     }
     else {
         apr_size_t dsize = size - AP_SLOTMEM_OFFSET;

 static void store_slotmem(ap_slotmem_instance_t *slotmem)
 {
     apr_file_t *fp;
     apr_status_t rv;
     apr_size_t nbytes;
     const char *storename;
+    unsigned char digest[APR_MD5_DIGESTSIZE];
 
     storename = slotmem_filename(slotmem->gpool, slotmem->name, 1);
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02334)
                  "storing %s", storename);
 

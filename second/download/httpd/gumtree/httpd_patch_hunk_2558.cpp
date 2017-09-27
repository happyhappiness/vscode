     avg_id_len = hints && hints->avg_id_len ? hints->avg_id_len : 30;
     num_idx = (shm_segsize) / (avg_obj_size + avg_id_len);
     num_subcache = 256;
     while ((num_idx / num_subcache) < (2 * num_subcache))
         num_subcache /= 2;
     num_idx /= num_subcache;
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                 "for %" APR_SIZE_T_FMT " bytes (%" APR_SIZE_T_FMT 
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00822)
+                 "for %" APR_SIZE_T_FMT " bytes (%" APR_SIZE_T_FMT
                  " including header), recommending %u subcaches, "
                  "%u indexes each", shm_segsize,
                  shm_segsize + sizeof(SHMCBHeader), num_subcache, num_idx);
     if (num_idx < 5) {
         /* we're still too small, bail out */
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00823)
                      "shared memory segment too small");
         return APR_ENOSPC;
     }
     /* OK, we're sorted */
     ctx->header = header = shm_segment;
     header->stat_stores = 0;

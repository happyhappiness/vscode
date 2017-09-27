                      "socache");
         return rv;
     }
 
     shm_segment = apr_shm_baseaddr_get(ctx->shm);
     shm_segsize = apr_shm_size_get(ctx->shm);
-    if (shm_segsize < (5 * sizeof(SHMCBHeader))) {
+    if (shm_segsize < (5 * ALIGNED_HEADER_SIZE)) {
         /* the segment is ridiculously small, bail out */
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00820)
                      "shared memory segment too small");
         return APR_ENOSPC;
     }
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00821)
                  "shmcb_init allocated %" APR_SIZE_T_FMT
                  " bytes of shared memory",
                  shm_segsize);
     /* Discount the header */
-    shm_segsize -= sizeof(SHMCBHeader);
+    shm_segsize -= ALIGNED_HEADER_SIZE;
     /* Select index size based on average object size hints, if given. */
     avg_obj_size = hints && hints->avg_obj_size ? hints->avg_obj_size : 150;
     avg_id_len = hints && hints->avg_id_len ? hints->avg_id_len : 30;
     num_idx = (shm_segsize) / (avg_obj_size + avg_id_len);
     num_subcache = 256;
     while ((num_idx / num_subcache) < (2 * num_subcache))
         num_subcache /= 2;
     num_idx /= num_subcache;
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00822)
                  "for %" APR_SIZE_T_FMT " bytes (%" APR_SIZE_T_FMT
                  " including header), recommending %u subcaches, "
                  "%u indexes each", shm_segsize,
-                 shm_segsize + sizeof(SHMCBHeader), num_subcache, num_idx);
+                 shm_segsize + ALIGNED_HEADER_SIZE,
+                 num_subcache, num_idx);
     if (num_idx < 5) {
         /* we're still too small, bail out */
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00823)
                      "shared memory segment too small");
         return APR_ENOSPC;
     }

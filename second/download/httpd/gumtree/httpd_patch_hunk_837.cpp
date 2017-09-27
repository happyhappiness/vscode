         ssl_die();
     }
     shm_segment = apr_shm_baseaddr_get(mc->pSessionCacheDataMM);
     shm_segsize = apr_shm_size_get(mc->pSessionCacheDataMM);
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                 "shmcb_init allocated %" APR_SIZE_T_FMT 
+                 "shmcb_init allocated %" APR_SIZE_T_FMT
                  " bytes of shared memory",
                  shm_segsize);
     if (!shmcb_init_memory(s, shm_segment, shm_segsize)) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                      "Failure initialising 'shmcb' shared memory");
         ssl_die();
     }
     ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                  "Shared memory session cache initialised");
 
-    /* 
-     * Success ... we hack the memory block into place by cheating for
-     * now and stealing a member variable the original shared memory
-     * cache was using. :-)
+    /*
+     * Success ...
      */
-    mc->tSessionCacheDataTable = (table_t *) shm_segment;
+    mc->tSessionCacheDataTable = shm_segment;
     return;
 }
 
 void ssl_scache_shmcb_kill(server_rec *s)
 {
     SSLModConfigRec *mc = myModConfig(s);

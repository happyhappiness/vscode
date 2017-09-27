         if (rv || !(sb_shared = apr_shm_baseaddr_get(ap_scoreboard_shm))) {
             return HTTP_INTERNAL_SERVER_ERROR;
         }
         memset(sb_shared, 0, scoreboard_size);
         ap_init_scoreboard(sb_shared);
     }
-    else 
+    else
 #endif
     {
         /* A simple malloc will suffice */
         void *sb_mem = calloc(1, scoreboard_size);
         if (sb_mem == NULL) {
             ap_log_error(APLOG_MARK, APLOG_CRIT, 0, NULL,

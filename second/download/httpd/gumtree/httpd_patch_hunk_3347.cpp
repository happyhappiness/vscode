     ap_run_child_init(pchild, ap_server_conf);
 
     /* Create an event semaphore used to trigger other threads to shutdown */
     rc = DosCreateEventSem(NULL, &shutdown_event, 0, FALSE);
 
     if (rc) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf, APLOGNO(00189)
                      "unable to create shutdown semaphore, exiting");
         clean_child_exit(APEXIT_CHILDFATAL);
     }
 
     /* Gain access to the scoreboard. */
     rc = DosGetNamedSharedMem(&sb_mem, ap_scoreboard_fname,
                               PAG_READ|PAG_WRITE);
 
     if (rc) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf, APLOGNO(00190)
                      "scoreboard not readable in child, exiting");
         clean_child_exit(APEXIT_CHILDFATAL);
     }
 
     ap_calc_scoreboard_size();
     ap_init_scoreboard(sb_mem);
 
     /* Gain access to the accpet mutex */
     rc = DosOpenMutexSem(NULL, &ap_mpm_accept_mutex);
 
     if (rc) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf, APLOGNO(00191)
                      "accept mutex couldn't be accessed in child, exiting");
         clean_child_exit(APEXIT_CHILDFATAL);
     }
 
     /* Find our pid in the scoreboard so we know what slot our parent allocated us */
     for (child_slot = 0; ap_scoreboard_image->parent[child_slot].pid != my_pid && child_slot < HARD_SERVER_LIMIT; child_slot++);
 
     if (child_slot == HARD_SERVER_LIMIT) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(00192)
                      "child pid not found in scoreboard, exiting");
         clean_child_exit(APEXIT_CHILDFATAL);
     }
 
     ap_my_generation = ap_scoreboard_image->parent[child_slot].generation;
     memset(ap_scoreboard_image->servers[child_slot], 0, sizeof(worker_score) * HARD_THREAD_LIMIT);

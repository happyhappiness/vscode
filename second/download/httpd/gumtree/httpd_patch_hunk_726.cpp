                 ps_record = ap_get_scoreboard_process(i);
 
                 if (ws_record->start_time == 0L)
                     req_time = 0L;
                 else
                     req_time = (long)
-                        ((ws_record->stop_time - 
+                        ((ws_record->stop_time -
                           ws_record->start_time) / 1000);
                 if (req_time < 0L)
                     req_time = 0L;
 
                 lres = ws_record->access_count;
                 my_lres = ws_record->my_access_count;
                 conn_lres = ws_record->conn_count;
                 bytes = ws_record->bytes_served;
                 my_bytes = ws_record->my_bytes_served;
                 conn_bytes = ws_record->conn_bytes;
+                if (ws_record->pid) { /* MPM sets per-worker pid and generation */
+                    worker_pid = ws_record->pid;
+                    worker_generation = ws_record->generation;
+                }
+                else {
+                    worker_pid = ps_record->pid;
+                    worker_generation = ps_record->generation;
+                }
 
                 if (no_table_report) {
                     if (ws_record->status == SERVER_DEAD)
                         ap_rprintf(r,
                                    "<b>Server %d-%d</b> (-): %d|%lu|%lu [",
-                                   i, (int)ps_record->generation,
+                                   i, (int)worker_generation,
                                    (int)conn_lres, my_lres, lres);
                     else
                         ap_rprintf(r,
                                    "<b>Server %d-%d</b> (%"
                                    APR_PID_T_FMT "): %d|%lu|%lu [",
-                                   i, (int) ps_record->generation,
-                                   ps_record->pid,
+                                   i, (int) worker_generation,
+                                   worker_pid,
                                    (int)conn_lres, my_lres, lres);
-                    
+
                     switch (ws_record->status) {
                     case SERVER_READY:
                         ap_rputs("Ready", r);
                         break;
                     case SERVER_STARTING:
                         ap_rputs("Starting", r);

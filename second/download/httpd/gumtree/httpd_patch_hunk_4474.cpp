     int pid;
 
     if (slot + 1 > retained->max_daemons_limit) {
         retained->max_daemons_limit = slot + 1;
     }
 
+    if (ap_scoreboard_image->parent[slot].pid != 0) {
+        /* XXX replace with assert or remove ? */
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(03455)
+                 "BUG: Scoreboard slot %d should be empty but is "
+                 "in use by pid %" APR_PID_T_FMT,
+                 slot, ap_scoreboard_image->parent[slot].pid);
+        return -1;
+    }
+
     if (one_process) {
         my_bucket = &all_buckets[0];
 
         set_signals();
         event_note_child_started(slot, getpid());
         child_main(slot, 0);

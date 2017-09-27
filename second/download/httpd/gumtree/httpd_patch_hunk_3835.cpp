 
     free(threads);
 
     clean_child_exit(resource_shortage ? APEXIT_CHILDSICK : 0);
 }
 
-static int make_child(server_rec * s, int slot)
+static int make_child(server_rec * s, int slot, int bucket)
 {
     int pid;
 
     if (slot + 1 > retained->max_daemons_limit) {
         retained->max_daemons_limit = slot + 1;
     }
 
     if (one_process) {
+        my_bucket = &all_buckets[0];
+
         set_signals();
         event_note_child_started(slot, getpid());
-        child_main(slot);
+        child_main(slot, 0);
         /* NOTREACHED */
+        ap_assert(0);
+        return -1;
     }
 
     if ((pid = fork()) == -1) {
         ap_log_error(APLOG_MARK, APLOG_ERR, errno, s, APLOGNO(00481)
                      "fork: Unable to fork new process");
 

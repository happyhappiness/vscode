         /* XXX: if it takes longer than 1 second for all our children
          * to start up and get into IDLE state then we may spawn an
          * extra child
          */
         if (pid.pid != -1) {
             processed_status = ap_process_child_status(&pid, exitwhy, status);
+            child_slot = ap_find_child_by_pid(&pid);
             if (processed_status == APEXIT_CHILDFATAL) {
-                mpm_state = AP_MPMQ_STOPPING;
-                return DONE;
+                /* fix race condition found in PR 39311
+                 * A child created at the same time as a graceful happens 
+                 * can find the lock missing and create a fatal error.
+                 * It is not fatal for the last generation to be in this state.
+                 */
+                if (child_slot < 0
+                    || ap_get_scoreboard_process(child_slot)->generation
+                       == retained->my_generation) {
+                    mpm_state = AP_MPMQ_STOPPING;
+                    return DONE;
+                }
+                else {
+                    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf, APLOGNO(00166)
+                                 "Ignoring fatal error in child of previous "
+                                 "generation (pid %ld).",
+                                 (long)pid.pid);
+                }
             }
 
             /* non-fatal death... note that it's gone in the scoreboard. */
-            child_slot = ap_find_child_by_pid(&pid);
             if (child_slot >= 0) {
                 (void) ap_update_child_status_from_indexes(child_slot, 0, SERVER_DEAD,
                                                            (request_rec *) NULL);
+                prefork_note_child_killed(child_slot, 0, 0);
                 if (processed_status == APEXIT_CHILDSICK) {
                     /* child detected a resource shortage (E[NM]FILE, ENOBUFS, etc)
                      * cut the fork rate to the minimum
                      */
-                    idle_spawn_rate = 1;
+                    retained->idle_spawn_rate = 1;
                 }
                 else if (remaining_children_to_start
                     && child_slot < ap_daemons_limit) {
                     /* we're still doing a 1-for-1 replacement of dead
                      * children with new children
                      */

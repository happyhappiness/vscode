                    ap_state_query(AP_SQ_CONFIG_GEN));
         ap_rprintf(r, "<dt>Parent Server MPM Generation: %d</dt>\n",
                    (int)mpm_generation);
         ap_rputs("<dt>Server uptime: ", r);
         show_time(r, up_time);
         ap_rputs("</dt>\n", r);
-        ap_get_loadavg(&t);
         ap_rprintf(r, "<dt>Server load: %.2f %.2f %.2f</dt>\n",
                    t.loadavg, t.loadavg5, t.loadavg15);
     }
+    else {
+        ap_rvputs(r, ap_get_server_name(r), "\n", NULL);
+        ap_rvputs(r, "ServerVersion: ",
+                  ap_get_server_description(), "\n", NULL);
+        ap_rvputs(r, "ServerMPM: ",
+                  ap_show_mpm(), "\n", NULL);
+        ap_rvputs(r, "Server Built: ",
+                  ap_get_server_built(), "\n", NULL);
+        ap_rvputs(r, "CurrentTime: ",
+                  ap_ht_time(r->pool, nowtime, DEFAULT_TIME_FORMAT, 0),
+                             "\n", NULL);
+        ap_rvputs(r, "RestartTime: ",
+                  ap_ht_time(r->pool,
+                             ap_scoreboard_image->global->restart_time,
+                             DEFAULT_TIME_FORMAT, 0),
+                  "\n", NULL);
+        ap_rprintf(r, "ParentServerConfigGeneration: %d\n",
+                   ap_state_query(AP_SQ_CONFIG_GEN));
+        ap_rprintf(r, "ParentServerMPMGeneration: %d\n",
+                   (int)mpm_generation);
+        ap_rprintf(r, "ServerUptimeSeconds: %u\n",
+                   up_time);
+        ap_rputs("ServerUptime:", r);
+        show_time(r, up_time);
+        ap_rputs("\n", r);
+        ap_rprintf(r, "Load1: %.2f\nLoad5: %.2f\nLoad15: %.2f\n",
+                   t.loadavg, t.loadavg5, t.loadavg15);
+    }
 
     if (ap_extended_status) {
         if (short_report) {
             ap_rprintf(r, "Total Accesses: %lu\nTotal kBytes: %"
                        APR_OFF_T_FMT "\n",
                        count, kbcount);
 
 #ifdef HAVE_TIMES
             /* Allow for OS/2 not having CPU stats */
+            ap_rprintf(r, "CPUUser: %g\nCPUSystem: %g\nCPUChildrenUser: %g\nCPUChildrenSystem: %g\n",
+                       tu / tick, ts / tick, tcu / tick, tcs / tick);
+
             if (ts || tu || tcu || tcs)
                 ap_rprintf(r, "CPULoad: %g\n",
                            (tu + ts + tcu + tcs) / tick / up_time * 100.);
 #endif
 
             ap_rprintf(r, "Uptime: %ld\n", (long) (up_time));

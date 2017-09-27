 
     if (!short_report)
         ap_rputs("</dl>", r);
 
     if (is_async) {
         int write_completion = 0, lingering_close = 0, keep_alive = 0,
-            connections = 0;
+            connections = 0, stopping = 0, procs = 0;
         /*
          * These differ from 'busy' and 'ready' in how gracefully finishing
          * threads are counted. XXX: How to make this clear in the html?
          */
         int busy_workers = 0, idle_workers = 0;
         if (!short_report)
             ap_rputs("\n\n<table rules=\"all\" cellpadding=\"1%\">\n"
-                     "<tr><th rowspan=\"2\">PID</th>"
+                     "<tr><th rowspan=\"2\">Slot</th>"
+                         "<th rowspan=\"2\">PID</th>"
+                         "<th rowspan=\"2\">Stopping</th>"
                          "<th colspan=\"2\">Connections</th>\n"
                          "<th colspan=\"2\">Threads</th>"
-                         "<th colspan=\"4\">Async connections</th></tr>\n"
+                         "<th colspan=\"3\">Async connections</th></tr>\n"
                      "<tr><th>total</th><th>accepting</th>"
-                         "<th>busy</th><th>idle</th><th>writing</th>"
-                         "<th>keep-alive</th><th>closing</th></tr>\n", r);
+                         "<th>busy</th><th>idle</th>"
+                         "<th>writing</th><th>keep-alive</th><th>closing</th></tr>\n", r);
         for (i = 0; i < server_limit; ++i) {
             ps_record = ap_get_scoreboard_process(i);
             if (ps_record->pid) {
                 connections      += ps_record->connections;
                 write_completion += ps_record->write_completion;
                 keep_alive       += ps_record->keep_alive;
                 lingering_close  += ps_record->lingering_close;
                 busy_workers     += thread_busy_buffer[i];
                 idle_workers     += thread_idle_buffer[i];
-                if (!short_report)
-                    ap_rprintf(r, "<tr><td>%" APR_PID_T_FMT "</td><td>%u</td>"
-                                      "<td>%s</td><td>%u</td><td>%u</td>"
+                if (!short_report) {
+                    const char *dying = "no";
+                    const char *old = "";
+                    if (ps_record->quiescing) {
+                        dying = "yes";
+                        stopping++;
+                    }
+                    if (ps_record->generation != mpm_generation)
+                        old = " (old gen)";
+                    procs++;
+                    ap_rprintf(r, "<tr><td>%u</td><td>%" APR_PID_T_FMT "</td>"
+                                      "<td>%s%s</td>"
+                                      "<td>%u</td><td>%s</td>"
+                                      "<td>%u</td><td>%u</td>"
                                       "<td>%u</td><td>%u</td><td>%u</td>"
                                       "</tr>\n",
-                               ps_record->pid, ps_record->connections,
+                               i, ps_record->pid,
+                               dying, old,
+                               ps_record->connections,
                                ps_record->not_accepting ? "no" : "yes",
-                               thread_busy_buffer[i], thread_idle_buffer[i],
+                               thread_busy_buffer[i],
+                               thread_idle_buffer[i],
                                ps_record->write_completion,
                                ps_record->keep_alive,
                                ps_record->lingering_close);
+                }
             }
         }
         if (!short_report) {
-            ap_rprintf(r, "<tr><td>Sum</td><td>%d</td><td>&nbsp;</td><td>%d</td>"
-                          "<td>%d</td><td>%d</td><td>%d</td><td>%d</td>"
+            ap_rprintf(r, "<tr><td>Sum</td>"
+                          "<td>%d</td><td>%d</td>"
+                          "<td>%d</td><td>&nbsp;</td>"
+                          "<td>%d</td><td>%d</td>"
+                          "<td>%d</td><td>%d</td><td>%d</td>"
                           "</tr>\n</table>\n",
-                          connections, busy_workers, idle_workers,
+                          procs, stopping,
+                          connections,
+                          busy_workers, idle_workers,
                           write_completion, keep_alive, lingering_close);
-
         }
         else {
             ap_rprintf(r, "ConnsTotal: %d\n"
                           "ConnsAsyncWriting: %d\n"
                           "ConnsAsyncKeepAlive: %d\n"
                           "ConnsAsyncClosing: %d\n",

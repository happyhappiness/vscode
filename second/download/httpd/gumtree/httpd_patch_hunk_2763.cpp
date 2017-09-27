     if (!short_report)
         ap_rprintf(r, "<dt>%d requests currently being processed, "
                       "%d idle workers</dt>\n", busy, ready);
     else
         ap_rprintf(r, "BusyWorkers: %d\nIdleWorkers: %d\n", busy, ready);
 
+    if (!short_report)
+        ap_rputs("</dl>", r);
+
+    if (is_async) {
+        int write_completion = 0, lingering_close = 0, keep_alive = 0,
+            connections = 0;
+        /*
+         * These differ from 'busy' and 'ready' in how gracefully finishing
+         * threads are counted. XXX: How to make this clear in the html?
+         */
+        int busy_workers = 0, idle_workers = 0;
+        if (!short_report)
+            ap_rputs("\n\n<table rules=\"all\" cellpadding=\"1%\">\n"
+                     "<tr><th rowspan=\"2\">PID</th>"
+                         "<th colspan=\"2\">Connections</th>\n"
+                         "<th colspan=\"2\">Threads</th>"
+                         "<th colspan=\"4\">Async connections</th></tr>\n"
+                     "<tr><th>total</th><th>accepting</th>"
+                         "<th>busy</th><th>idle</th><th>writing</th>"
+                         "<th>keep-alive</th><th>closing</th></tr>\n", r);
+        for (i = 0; i < server_limit; ++i) {
+            ps_record = ap_get_scoreboard_process(i);
+            if (ps_record->pid) {
+                connections      += ps_record->connections;
+                write_completion += ps_record->write_completion;
+                keep_alive       += ps_record->keep_alive;
+                lingering_close  += ps_record->lingering_close;
+                busy_workers     += thread_busy_buffer[i];
+                idle_workers     += thread_idle_buffer[i];
+                if (!short_report)
+                    ap_rprintf(r, "<tr><td>%" APR_PID_T_FMT "</td><td>%u</td>"
+                                      "<td>%s</td><td>%u</td><td>%u</td>"
+                                      "<td>%u</td><td>%u</td><td>%u</td>"
+                                      "</tr>\n",
+                               ps_record->pid, ps_record->connections,
+                               ps_record->not_accepting ? "no" : "yes",
+                               thread_busy_buffer[i], thread_idle_buffer[i],
+                               ps_record->write_completion,
+                               ps_record->keep_alive,
+                               ps_record->lingering_close);
+            }
+        }
+        if (!short_report) {
+            ap_rprintf(r, "<tr><td>Sum</td><td>%d</td><td>&nbsp;</td><td>%d</td>"
+                          "<td>%d</td><td>%d</td><td>%d</td><td>%d</td>"
+                          "</tr>\n</table>\n",
+                          connections, busy_workers, idle_workers,
+                          write_completion, keep_alive, lingering_close);
+
+        }
+        else {
+            ap_rprintf(r, "ConnsTotal: %d\n"
+                          "ConnsAsyncWriting: %d\n"
+                          "ConnsAsyncKeepAlive: %d\n"
+                          "ConnsAsyncClosing: %d\n",
+                       connections, write_completion, keep_alive,
+                       lingering_close);
+        }
+    }
+
     /* send the scoreboard 'table' out */
     if (!short_report)
-        ap_rputs("</dl><pre>", r);
+        ap_rputs("<pre>", r);
     else
         ap_rputs("Scoreboard: ", r);
 
+    written = 0;
     for (i = 0; i < server_limit; ++i) {
         for (j = 0; j < thread_limit; ++j) {
             int indx = (i * thread_limit) + j;
-            ap_rputc(stat_buffer[indx], r);
-            if ((indx % STATUS_MAXLINE == (STATUS_MAXLINE - 1))
-                && !short_report)
-                ap_rputs("\n", r);
+            if (stat_buffer[indx] != status_flags[SERVER_DISABLED]) {
+                ap_rputc(stat_buffer[indx], r);
+                if ((written % STATUS_MAXLINE == (STATUS_MAXLINE - 1))
+                    && !short_report)
+                    ap_rputs("\n", r);
+                written++;
+            }
         }
     }
 
+
     if (short_report)
         ap_rputs("\n", r);
     else {
-        ap_rputs("</pre>\n", r);
-        ap_rputs("<p>Scoreboard Key:<br />\n", r);
-        ap_rputs("\"<b><code>_</code></b>\" Waiting for Connection, \n", r);
-        ap_rputs("\"<b><code>S</code></b>\" Starting up, \n", r);
-        ap_rputs("\"<b><code>R</code></b>\" Reading Request,<br />\n", r);
-        ap_rputs("\"<b><code>W</code></b>\" Sending Reply, \n", r);
-        ap_rputs("\"<b><code>K</code></b>\" Keepalive (read), \n", r);
-        ap_rputs("\"<b><code>D</code></b>\" DNS Lookup,<br />\n", r);
-        ap_rputs("\"<b><code>C</code></b>\" Closing connection, \n", r);
-        ap_rputs("\"<b><code>L</code></b>\" Logging, \n", r);
-        ap_rputs("\"<b><code>G</code></b>\" Gracefully finishing,<br /> \n", r);
-        ap_rputs("\"<b><code>I</code></b>\" Idle cleanup of worker, \n", r);
-        ap_rputs("\"<b><code>.</code></b>\" Open slot with no current process</p>\n", r);
-        ap_rputs("<p />\n", r);
+        ap_rputs("</pre>\n"
+                 "<p>Scoreboard Key:<br />\n"
+                 "\"<b><code>_</code></b>\" Waiting for Connection, \n"
+                 "\"<b><code>S</code></b>\" Starting up, \n"
+                 "\"<b><code>R</code></b>\" Reading Request,<br />\n"
+                 "\"<b><code>W</code></b>\" Sending Reply, \n"
+                 "\"<b><code>K</code></b>\" Keepalive (read), \n"
+                 "\"<b><code>D</code></b>\" DNS Lookup,<br />\n"
+                 "\"<b><code>C</code></b>\" Closing connection, \n"
+                 "\"<b><code>L</code></b>\" Logging, \n"
+                 "\"<b><code>G</code></b>\" Gracefully finishing,<br /> \n"
+                 "\"<b><code>I</code></b>\" Idle cleanup of worker, \n"
+                 "\"<b><code>.</code></b>\" Open slot with no current process,<br />\n"
+                 "<p />\n", r);
         if (!ap_extended_status) {
             int j;
             int k = 0;
-            ap_rputs("PID Key: <br />\n", r);
-            ap_rputs("<pre>\n", r);
+            ap_rputs("PID Key: <br />\n"
+                     "<pre>\n", r);
             for (i = 0; i < server_limit; ++i) {
                 for (j = 0; j < thread_limit; ++j) {
                     int indx = (i * thread_limit) + j;
 
                     if (stat_buffer[indx] != '.') {
                         ap_rprintf(r, "   %" APR_PID_T_FMT

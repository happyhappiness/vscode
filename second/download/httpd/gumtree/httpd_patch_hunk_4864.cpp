                    ap_state_query(AP_SQ_CONFIG_GEN));
         ap_rprintf(r, "<dt>Parent Server MPM Generation: %d</dt>\n",
                    (int)mpm_generation);
         ap_rputs("<dt>Server uptime: ", r);
         show_time(r, up_time);
         ap_rputs("</dt>\n", r);
+        ap_get_loadavg(&t);
+        ap_rprintf(r, "<dt>Server load: %.2f %.2f %.2f</dt>\n",
+                   t.loadavg, t.loadavg5, t.loadavg15);
     }
 
     if (ap_extended_status) {
         if (short_report) {
             ap_rprintf(r, "Total Accesses: %lu\nTotal kBytes: %"
                        APR_OFF_T_FMT "\n",

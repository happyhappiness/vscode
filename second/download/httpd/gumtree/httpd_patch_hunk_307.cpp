             ap_rputs("<hr />To obtain a full report with current status "
                      "information you need to use the "
                      "<code>ExtendedStatus On</code> directive.\n", r);
         }
     }
 
+    {
+        /* Run extension hooks to insert extra content. */
+        int flags = 
+            (short_report ? AP_STATUS_SHORT : 0) | 
+            (no_table_report ? AP_STATUS_NOTABLE : 0) |
+            (ap_extended_status ? AP_STATUS_EXTENDED : 0);
+        
+        ap_run_status_hook(r, flags);
+    }
+
     if (!short_report) {
         ap_rputs(ap_psignature("<hr />\n",r), r);
         ap_rputs("</body></html>\n", r);
     }
 
     return 0;

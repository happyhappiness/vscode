                         } else
                             ap_rputs(",", r);
                     }
                 }
             }
 
-            ap_rputs("\n", r);
-            ap_rputs("</pre>\n", r);
+            ap_rputs("\n"
+                     "</pre>\n", r);
         }
     }
 
     if (ap_extended_status && !short_report) {
         if (no_table_report)
             ap_rputs("<hr /><h2>Server Details</h2>\n\n", r);

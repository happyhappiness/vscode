         /* first try to attach to existing slotmem */
         if (next) {
             for (;;) {
                 if (strcmp(next->name, fname) == 0) {
                     /* we already have it */
                     *new = next;
+                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02603)
+                                 "create found %s in global list", fname);
                     return APR_SUCCESS;
                 }
                 if (!next->next) {
                      break;
                 }
                 next = next->next;
             }
         }
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02602)
+                     "create didn't find %s in global list", fname);
     }
     else {
         fbased = 0;
         fname = "none";
     }
 

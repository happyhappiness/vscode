         else if (strcEQ(w, "all")) {
             thisopt = SSL_PROTOCOL_ALL;
         }
         else {
             return apr_pstrcat(parms->temp_pool,
                                parms->cmd->name,
-                               ": Illegal protocol '",
-                               w, "'", NULL);
+                               ": Illegal protocol '", w, "'", NULL);
         }
 
         if (action == '-') {
             *options &= ~thisopt;
         }
         else if (action == '+') {
             *options |= thisopt;
         }
         else {
+            if (*options != SSL_PROTOCOL_NONE) {
+                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, parms->server, APLOGNO(02532)
+                             "%s: Protocol '%s' overrides already set parameter(s). "
+                             "Check if a +/- prefix is missing.",
+                             parms->cmd->name, w);
+            }
             *options = thisopt;
         }
     }
 
     return NULL;
 }

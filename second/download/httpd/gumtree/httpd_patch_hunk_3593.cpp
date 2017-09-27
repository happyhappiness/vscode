         for (j = i + 1; j < nelts; j++) {
             size_t ltabj = strlen(tab[j]);
 
             /* must not use the same argument name twice */
             if (!strcmp(tab[i], tab[j])) {
                 return apr_psprintf(pool,
-                                   "argument name conflict in macro '%s' (%s): "
+                                    "argument name conflict in macro '%s' (%s): "
                                     "argument '%s': #%d and #%d, "
                                     "change argument names!",
                                     macro->name, macro->location,
                                     tab[i], i + 1, j + 1);
             }
 
             /* warn about common prefix, but only if non empty names */
             if (ltabi && ltabj &&
                 !strncmp(tab[i], tab[j], ltabi < ltabj ? ltabi : ltabj)) {
-                ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_WARNING,
-                             0, NULL,
+                ap_log_error(APLOG_MARK, APLOG_WARNING,
+                             0, NULL, APLOGNO(02797)
                              "macro '%s' (%s): "
-                            "argument name prefix conflict (%s #%d and %s #%d),"
-                             " be careful about your macro definition!",
+                             "argument name prefix conflict (%s #%d and %s #%d), "
+                             "be careful about your macro definition!",
                              macro->name, macro->location,
                              tab[i], i + 1, tab[j], j + 1);
             }
         }
     }
 

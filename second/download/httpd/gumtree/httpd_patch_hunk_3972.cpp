     /* Log the errors */
     /* ### should have a directive to log the first or all */
     for (errscan = err; errscan != NULL; errscan = errscan->prev) {
         if (errscan->desc == NULL)
             continue;
 
+        /* Intentional no APLOGNO */
         ap_log_rerror(APLOG_MARK, level, errscan->aprerr, r, "%s  [%d, #%d]",
                       errscan->desc, errscan->status, errscan->error_id);
     }
 }
 
 /*

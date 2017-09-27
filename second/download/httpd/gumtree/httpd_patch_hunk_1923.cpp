 
             strcpy(malformed, MALFORMED_MESSAGE);
             strncat(malformed, w, MALFORMED_HEADER_LENGTH_TO_SHOW);
 
             if (!buffer) {
                 /* Soak up all the script output - may save an outright kill */
-                while ((*getsfunc)(w, MAX_STRING_LEN - 1, getsfunc_data) > 0) {
+                while ((*getsfunc) (w, MAX_STRING_LEN - 1, getsfunc_data)) {
                     continue;
                 }
             }
 
             ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_TOCLIENT, 0, r,
                           "%s: %s", malformed,

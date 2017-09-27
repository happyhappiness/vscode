             }
         }
 #endif /*APR_CHARSET_EBCDIC*/
         if (!(l = strchr(w, ':'))) {
             if (!buffer) {
                 /* Soak up all the script output - may save an outright kill */
-                while ((*getsfunc) (w, MAX_STRING_LEN - 1, getsfunc_data)) {
+                while ((*getsfunc)(w, MAX_STRING_LEN - 1, getsfunc_data) > 0) {
                     continue;
                 }
             }
 
             ap_log_rerror(SCRIPT_LOG_MARK, APLOG_ERR|APLOG_TOCLIENT, 0, r,
                           "malformed header from script '%s': Bad header: %.30s",

         if (no > 9) {                /* Ordinary character. */
             if (c == '\\' && (*src == '$' || *src == '&'))
                 c = *src++;
             len++;
         }
         else if (no < nmatch && pmatch[no].rm_so < pmatch[no].rm_eo) {
-            if (UTIL_SIZE_MAX - len <= pmatch[no].rm_eo - pmatch[no].rm_so) {
-                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL,
-                             "integer overflow or out of memory condition." );
-                return NULL;
-            }
             len += pmatch[no].rm_eo - pmatch[no].rm_so;
         }
 
     }
 
     dest = dst = apr_pcalloc(p, len + 1);

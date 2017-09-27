 
     /* getting a subtype */
     while (apr_isspace(*cp)) {
         cp++;
     }
     if (!*cp) {
-        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss, APLOGNO(01601)
                      "Cannot get media subtype.");
         return (NULL);
     }
     ctp->subtype = cp;
     do {
         cp++;

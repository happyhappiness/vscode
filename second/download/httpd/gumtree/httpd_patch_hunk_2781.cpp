     /* getting a type */
     cp = mp;
     while (apr_isspace(*cp)) {
         cp++;
     }
     if (!*cp) {
-        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss, APLOGNO(01598)
                      "mod_mime: analyze_ct: cannot get media type from '%s'",
                      (const char *) mp);
         return (NULL);
     }
     ctp->type = cp;
     do {
         cp++;
     } while (*cp && (*cp != '/') && !apr_isspace(*cp) && (*cp != ';'));
     if (!*cp || (*cp == ';')) {
-        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss, APLOGNO(01599)
                      "Cannot get media type from '%s'",
                      (const char *) mp);
         return (NULL);
     }
     while (apr_isspace(*cp)) {
         cp++;
     }
     if (*cp != '/') {
-        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss, APLOGNO(01600)
                      "mod_mime: analyze_ct: cannot get media type from '%s'",
                      (const char *) mp);
         return (NULL);
     }
     ctp->type_len = cp - ctp->type;
 

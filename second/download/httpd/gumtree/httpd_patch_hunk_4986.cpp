                       r->filename, header);
         return NULL;
     }
 
     do {
         ++cp;
-    } while (*cp && apr_isspace(*cp));
+    } while (apr_isspace(*cp));
 
     if (!*cp) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00682)
                       "Syntax error in type map --- no header body: %s for %s",
                       r->filename, header);
         return NULL;

             ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01560)
                 "malformed header in meta file: %s", r->filename);
             return HTTP_INTERNAL_SERVER_ERROR;
         }
 
         *l++ = '\0';
-        while (*l && apr_isspace(*l))
+        while (apr_isspace(*l))
             ++l;
 
         if (!strcasecmp(w, "Content-type")) {
             char *tmp;
             /* Nuke trailing whitespace */
 

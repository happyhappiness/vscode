     char **names = (char **) macro->arguments->elts;
     apr_array_header_t *used;
     int i;
     const char *errmsg;
 
     if (macro->contents->nelts == 0) {
-        ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_WARNING, 0, NULL,
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL, APLOGNO(02799)
                      "macro '%s' (%s): empty contents!",
                      macro->name, macro->location);
         return NULL;            /* no need to further warnings... */
     }
 
     used = apr_array_make(pool, nelts, sizeof(char));

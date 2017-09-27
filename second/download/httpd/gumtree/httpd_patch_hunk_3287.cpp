         apr_file_t *dummy = NULL;
         apr_cmdtype_e cmdtype = APR_PROGRAM_ENV;
         fname = s->error_fname + 1;
 
         /* In 2.4 favor PROGRAM_ENV, accept "||prog" syntax for compatibility
          * and "|$cmd" to override the default.
-         * Any 2.2 backport would continue to favor SHELLCMD_ENV so there 
+         * Any 2.2 backport would continue to favor SHELLCMD_ENV so there
          * accept "||prog" to override, and "|$cmd" to ease conversion.
          */
         if (*fname == '|')
             ++fname;
         if (*fname == '$') {
             cmdtype = APR_SHELLCMD_ENV;
             ++fname;
         }
-	
+
         /* Spawn a new child logger.  If this is the main server_rec,
          * the new child must use a dummy stderr since the current
          * stderr might be a pipe to the old logger.  Otherwise, the
          * child inherits the parents stderr. */
         rc = log_child(p, fname, &dummy, cmdtype, is_main);
         if (rc != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL, APLOGNO(00089)
                          "Couldn't start ErrorLog process '%s'.",
                          s->error_fname + 1);
             return DONE;
         }
 
         s->error_log = dummy;

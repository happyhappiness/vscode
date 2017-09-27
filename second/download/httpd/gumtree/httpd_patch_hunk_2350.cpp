 
                 /*
                  * Ok, anything else now means a fatal error.
                  */
                 if (cpPassPhraseCur == NULL) {
                     if (nPassPhraseDialogCur && pkey_mtime &&
-                        !(isterm = isatty(fileno(stdout)))) /* XXX: apr_isatty() */
+                        !isatty(fileno(stdout))) /* XXX: apr_isatty() */
                     {
                         ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                                      pServ,
                                      "Init: Unable to read pass phrase "
                                      "[Hint: key introduced or changed "
                                      "before restart?]");

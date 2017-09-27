              * rather than attempting to temporarily rehook it to the terminal,
              * we print the prompt to stdout before EVP_read_pw_string turns
              * off tty echo
              */
             apr_file_open_stdout(&writetty, p);
 
-            ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
+            ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01968)
                          "Init: Requesting pass phrase via builtin terminal "
                          "dialog");
 #endif
         }
 
         /*
          * The first time display a header to inform the user about what
          * program he actually speaks to, which module is responsible for
          * this terminal dialog and why to the hell he has to enter
          * something...
          */
         if (*pnPassPhraseDialog == 1) {
-            apr_file_printf(writetty, "%s mod_ssl/%s (Pass Phrase Dialog)\n",
-                            AP_SERVER_BASEVERSION, MOD_SSL_VERSION);
+            apr_file_printf(writetty, "%s mod_ssl (Pass Phrase Dialog)\n",
+                            AP_SERVER_BASEVERSION);
             apr_file_printf(writetty, "Some of your private key files are encrypted for security reasons.\n");
             apr_file_printf(writetty, "In order to read them you have to provide the pass phrases.\n");
         }
         if (*pbPassPhraseDialogOnce) {
             *pbPassPhraseDialogOnce = FALSE;
             apr_file_printf(writetty, "\n");

 
     if (*mask & APHTP_NOFILE) {
         i--;
     }
     else {
         if (strlen(argv[i]) > (APR_PATH_MAX - 1)) {
-            apr_file_printf(errfile, "%s: filename too long\n", argv[0]);
+            apr_file_printf(errfile, "%s: filename too long" NL, argv[0]);
             exit(ERR_OVERFLOW);
         }
         *pwfilename = apr_pstrdup(pool, argv[i]);
         if (strlen(argv[i + 1]) > (MAX_STRING_LEN - 1)) {
-            apr_file_printf(errfile, "%s: username too long (> %d)\n",
+            apr_file_printf(errfile, "%s: username too long (> %d)" NL,
                 argv[0], MAX_STRING_LEN - 1);
             exit(ERR_OVERFLOW);
         }
     }
     *user = apr_pstrdup(pool, argv[i + 1]);
     if ((arg = strchr(*user, ':')) != NULL) {
         apr_file_printf(errfile, "%s: username contains illegal "
-                        "character '%c'\n", argv[0], *arg);
+                        "character '%c'" NL, argv[0], *arg);
         exit(ERR_BADUSER);
     }
     if (*mask & APHTP_NONINTERACTIVE) {
         if (strlen(argv[i + 2]) > (MAX_STRING_LEN - 1)) {
-            apr_file_printf(errfile, "%s: password too long (> %d)\n",
+            apr_file_printf(errfile, "%s: password too long (> %d)" NL,
                 argv[0], MAX_STRING_LEN);
             exit(ERR_OVERFLOW);
         }
         *password = apr_pstrdup(pool, argv[i + 2]);
     }
 }

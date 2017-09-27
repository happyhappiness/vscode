                 argv[0], MAX_STRING_LEN - 1);
             exit(ERR_OVERFLOW);
         }
     }
     *user = apr_pstrdup(pool, argv[i + 1]);
     if ((arg = strchr(*user, ':')) != NULL) {
-        apr_file_printf(errfile, "%s: username contains illegal character '%c'\n",
-                argv[0], *arg);
+        apr_file_printf(errfile, "%s: username contains illegal "
+                        "character '%c'\n", argv[0], *arg);
         exit(ERR_BADUSER);
     }
     if (*mask & APHTP_NONINTERACTIVE) {
         if (strlen(argv[i + 2]) > (MAX_STRING_LEN - 1)) {
             apr_file_printf(errfile, "%s: password too long (> %d)\n",
                 argv[0], MAX_STRING_LEN);

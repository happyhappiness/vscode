     char pwin[MAX_STRING_LEN];
     char pwv[MAX_STRING_LEN];
     unsigned int i;
     apr_size_t len = sizeof(pwin);
 
     if (apr_password_get("New password: ", pwin, &len) != APR_SUCCESS) {
-	fprintf(stderr, "password too long");
+        apr_file_printf(errfile, "password too long");
 	cleanup_tempfile_and_exit(5);
     }
     len = sizeof(pwin);
     apr_password_get("Re-type new password: ", pwv, &len);
     if (strcmp(pwin, pwv) != 0) {
-	fprintf(stderr, "They don't match, sorry.\n");
+        apr_file_printf(errfile, "They don't match, sorry.\n");
         cleanup_tempfile_and_exit(1);
     }
     pw = pwin;
     apr_file_printf(f, "%s:%s:", user, realm);
 
     /* Do MD5 stuff */

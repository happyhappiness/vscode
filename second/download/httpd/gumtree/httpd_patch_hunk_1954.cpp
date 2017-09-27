         if (seed_rand()) {
             break;
         }
         to64(&salt[0], rand(), 8);
         salt[8] = '\0';
 
-        cbuf = crypt(pw, salt);
-        if (cbuf == NULL) {
-            char errbuf[128];
-
-            apr_snprintf(record, rlen-1, "crypt() failed: %s", 
-                         apr_strerror(errno, errbuf, sizeof errbuf));
-            return ERR_PWMISMATCH;
-        }
-
-        apr_cpystrn(cpw, cbuf, sizeof(cpw) - 1);
+        apr_cpystrn(cpw, crypt(pw, salt), sizeof(cpw) - 1);
         if (strlen(pw) > 8) {
             char *truncpw = strdup(pw);
             truncpw[8] = '\0';
             if (!strcmp(cpw, crypt(truncpw, salt))) {
                 apr_file_printf(errfile, "Warning: Password truncated to 8 characters "
                                 "by CRYPT algorithm." NL);

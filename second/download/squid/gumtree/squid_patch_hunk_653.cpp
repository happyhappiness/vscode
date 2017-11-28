         switch (option) {
         case 'H':
 #if !HAS_URI_SUPPORT
             fprintf(stderr, "FATAL: Your LDAP library does not have URI support\n");
             exit(1);
 #endif
-            /* Fall thru to -h */
+        /* Fall thru to -h */
         case 'h':
             if (ldapServer) {
                 int len = strlen(ldapServer) + 1 + strlen(value) + 1;
-                char *newhost = (char*)malloc(len);
+                char *newhost = static_cast<char*>(xmalloc(len));
                 snprintf(newhost, len, "%s %s", ldapServer, value);
                 free(ldapServer);
                 ldapServer = newhost;
             } else {
                 ldapServer = xstrdup(value);
             }

             snprintf(newhost, len, "%s %s", ldapServer, value);
             free(ldapServer);
             ldapServer = newhost;
         } else {
             ldapServer = xstrdup(value);
         }
-        argc--;
-        argv++;
+        --argc;
+        ++argv;
     }
     if (!ldapServer)
         ldapServer = xstrdup("localhost");
 
     if (!basedn) {
         fprintf(stderr, "Usage: " PROGRAM_NAME " -b basedn [options] [ldap_server_name[:port]]...\n\n");

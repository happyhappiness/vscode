             break;
         default:
             if (strlen(argv[1]) > 2) {
                 value = argv[1] + 2;
             } else if (argc > 2) {
                 value = argv[2];
-                argv++;
-                argc--;
+                ++argv;
+                --argc;
             } else
                 value = "";
             break;
         }
-        argv++;
-        argc--;
+        ++argv;
+        --argc;
         switch (option) {
         case 'H':
 #if !HAS_URI_SUPPORT
             fprintf(stderr, "FATAL: Your LDAP library does not have URI support\n");
             exit(1);
 #endif

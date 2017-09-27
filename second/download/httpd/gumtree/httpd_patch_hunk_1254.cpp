 
             apr_file_printf(errfile, "Could not open passwd file %s for writing: %s\n",
                     argv[2],
                     apr_strerror(rv, errmsg, sizeof errmsg));
             exit(1);
         }
+        apr_cpystrn(user, argv[4], sizeof(user));
+        apr_cpystrn(realm, argv[3], sizeof(realm));
         apr_file_printf(errfile, "Adding password for %s in realm %s.\n",
-                    argv[4], argv[3]);
-        add_password(argv[4], argv[3], f);
+                    user, realm);
+        add_password(user, realm, f);
         apr_file_close(f);
         exit(0);
     }
     else if (argc != 4)
         usage();
 

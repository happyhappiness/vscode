                 *alg = ALG_CRYPT;
             }
             else if (*arg == 'b') {
                 *mask |= APHTP_NONINTERACTIVE;
                 args_left++;
             }
+            else if (*arg == 'D') {
+                *mask |= APHTP_DELUSER;
+            }
             else {
                 usage();
             }
         }
     }
 
     if ((*mask & APHTP_NEWFILE) && (*mask & APHTP_NOFILE)) {
         apr_file_printf(errfile, "%s: -c and -n options conflict\n", argv[0]);
         exit(ERR_SYNTAX);
     }
+    if ((*mask & APHTP_NEWFILE) && (*mask & APHTP_DELUSER)) {
+        apr_file_printf(errfile, "%s: -c and -D options conflict\n", argv[0]);
+        exit(ERR_SYNTAX);
+    }
+    if ((*mask & APHTP_NOFILE) && (*mask & APHTP_DELUSER)) {
+        apr_file_printf(errfile, "%s: -n and -D options conflict\n", argv[0]);
+        exit(ERR_SYNTAX);
+    }
     /*
      * Make sure we still have exactly the right number of arguments left
      * (the filename, the username, and possibly the password if -b was
      * specified).
      */
     if ((argc - i) != args_left) {

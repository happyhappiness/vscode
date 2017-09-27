         if (existing_file) {
             /*
              * Check that this existing file is readable and writable.
              */
             if (!accessible(pool, pwfilename, APR_READ | APR_APPEND)) {
                 apr_file_printf(errfile, "%s: cannot open file %s for "
-                                "read/write access\n", argv[0], pwfilename);
+                                "read/write access" NL, argv[0], pwfilename);
                 exit(ERR_FILEPERM);
             }
         }
         else {
             /*
              * Error out if -c was omitted for this non-existant file.
              */
             if (!(mask & APHTP_NEWFILE)) {
                 apr_file_printf(errfile,
-                        "%s: cannot modify file %s; use '-c' to create it\n",
+                        "%s: cannot modify file %s; use '-c' to create it" NL,
                         argv[0], pwfilename);
                 exit(ERR_FILEPERM);
             }
             /*
              * As it doesn't exist yet, verify that we can create it.
              */
             if (!accessible(pool, pwfilename, APR_CREATE | APR_WRITE)) {
-                apr_file_printf(errfile, "%s: cannot create file %s\n",
+                apr_file_printf(errfile, "%s: cannot create file %s" NL,
                                 argv[0], pwfilename);
                 exit(ERR_FILEPERM);
             }
         }
     }
 

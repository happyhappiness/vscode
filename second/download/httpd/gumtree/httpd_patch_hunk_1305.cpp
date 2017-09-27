     apr_file_printf(errfile, "\thtpasswd -n[mdps] username" NL);
     apr_file_printf(errfile, "\thtpasswd -nb[mdps] username password" NL);
     apr_file_printf(errfile, " -c  Create a new file." NL);
     apr_file_printf(errfile, " -n  Don't update file; display results on "
                     "stdout." NL);
     apr_file_printf(errfile, " -m  Force MD5 encryption of the password"
-#if defined(WIN32) || defined(TPF) || defined(NETWARE)
         " (default)"
-#endif
         "." NL);
     apr_file_printf(errfile, " -d  Force CRYPT encryption of the password"
-#if (!(defined(WIN32) || defined(TPF) || defined(NETWARE)))
-            " (default)"
-#endif
             "." NL);
     apr_file_printf(errfile, " -p  Do not encrypt the password (plaintext)." NL);
     apr_file_printf(errfile, " -s  Force SHA encryption of the password." NL);
     apr_file_printf(errfile, " -b  Use the password from the command line "
             "rather than prompting for it." NL);
     apr_file_printf(errfile, " -D  Delete the specified user." NL);
     apr_file_printf(errfile,
-            "On Windows, NetWare and TPF systems the '-m' flag is used by "
-            "default." NL);
+            "On other systems than Windows, NetWare and TPF the '-p' flag will "
+            "probably not work." NL);
     apr_file_printf(errfile,
-            "On all other systems, the '-p' flag will probably not work." NL);
+            "The SHA algorithm does not use a salt and is less secure than "
+            "the MD5 algorithm." NL);
     exit(ERR_SYNTAX);
 }
 
 /*
  * Check to see if the specified file can be opened for the given
  * access.

     strcat(record, "\n");
     return 0;
 }
 
 static void usage(void)
 {
-    apr_file_printf(errfile, "Usage:\n");
-    apr_file_printf(errfile, "\thtpasswd [-cmdpsD] passwordfile username\n");
+    apr_file_printf(errfile, "Usage:" NL);
+    apr_file_printf(errfile, "\thtpasswd [-cmdpsD] passwordfile username" NL);
     apr_file_printf(errfile, "\thtpasswd -b[cmdpsD] passwordfile username "
-                    "password\n\n");
-    apr_file_printf(errfile, "\thtpasswd -n[mdps] username\n");
-    apr_file_printf(errfile, "\thtpasswd -nb[mdps] username password\n");
-    apr_file_printf(errfile, " -c  Create a new file.\n");
+                    "password" NL NL);
+    apr_file_printf(errfile, "\thtpasswd -n[mdps] username" NL);
+    apr_file_printf(errfile, "\thtpasswd -nb[mdps] username password" NL);
+    apr_file_printf(errfile, " -c  Create a new file." NL);
     apr_file_printf(errfile, " -n  Don't update file; display results on "
-                    "stdout.\n");
+                    "stdout." NL);
     apr_file_printf(errfile, " -m  Force MD5 encryption of the password"
 #if defined(WIN32) || defined(TPF) || defined(NETWARE)
         " (default)"
 #endif
-        ".\n");
+        "." NL);
     apr_file_printf(errfile, " -d  Force CRYPT encryption of the password"
 #if (!(defined(WIN32) || defined(TPF) || defined(NETWARE)))
             " (default)"
 #endif
-            ".\n");
-    apr_file_printf(errfile, " -p  Do not encrypt the password (plaintext).\n");
-    apr_file_printf(errfile, " -s  Force SHA encryption of the password.\n");
+            "." NL);
+    apr_file_printf(errfile, " -p  Do not encrypt the password (plaintext)." NL);
+    apr_file_printf(errfile, " -s  Force SHA encryption of the password." NL);
     apr_file_printf(errfile, " -b  Use the password from the command line "
-            "rather than prompting for it.\n");
-    apr_file_printf(errfile, " -D  Delete the specified user.\n");
+            "rather than prompting for it." NL);
+    apr_file_printf(errfile, " -D  Delete the specified user." NL);
     apr_file_printf(errfile,
             "On Windows, NetWare and TPF systems the '-m' flag is used by "
-            "default.\n");
+            "default." NL);
     apr_file_printf(errfile,
-            "On all other systems, the '-p' flag will probably not work.\n");
+            "On all other systems, the '-p' flag will probably not work." NL);
     exit(ERR_SYNTAX);
 }
 
 /*
  * Check to see if the specified file can be opened for the given
  * access.

 	getword(x, l, ':');
 	if (strcmp(user, w) || strcmp(realm, x)) {
 	    putline(tfp, line);
 	    continue;
 	}
 	else {
-	    printf("Changing password for user %s in realm %s\n", user, realm);
+            apr_file_printf(errfile, "Changing password for user %s in realm %s\n", 
+                    user, realm);
 	    add_password(user, realm, tfp);
 	    found = 1;
 	}
     }
     if (!found) {
-	printf("Adding user %s in realm %s\n", user, realm);
+        apr_file_printf(errfile, "Adding user %s in realm %s\n", user, realm);
 	add_password(user, realm, tfp);
     }
     apr_file_close(f);
-#if defined(OS2) || defined(WIN32)
-    sprintf(command, "copy \"%s\" \"%s\"", tn, argv[1]);
-#else
-    sprintf(command, "cp %s %s", tn, argv[1]);
-#endif
 
-#ifdef OMIT_DELONCLOSE
-    apr_file_close(tfp);
-    system(command);
-    apr_file_remove(tn, cntxt);
-#else
-    system(command);
+    /* The temporary file has all the data, just copy it to the new location.
+     */
+    if (apr_file_copy(dirname, argv[1], APR_FILE_SOURCE_PERMS, cntxt) !=
+                APR_SUCCESS) {
+        apr_file_printf(errfile, "%s: unable to update file %s\n", 
+                        argv[0], argv[1]);
+    }
     apr_file_close(tfp);
-#endif
 
     return 0;
 }

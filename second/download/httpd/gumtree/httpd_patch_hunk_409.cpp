     }
 
     /*
      * We can access the files the right way, and we have a record
      * to add or update.  Let's do it..
      */
-    tn = get_tempname(pool);
-    if (apr_file_mktemp(&ftemp, tn, 0, pool) != APR_SUCCESS) {
+    if (apr_temp_dir_get((const char**)&dirname, pool) != APR_SUCCESS) {
+        apr_file_printf(errfile, "%s: could not determine temp dir\n",
+                        argv[0]);
+        exit(ERR_FILEPERM);
+    }
+    dirname = apr_psprintf(pool, "%s/%s", dirname, tn);
+
+    if (apr_file_mktemp(&ftemp, dirname, 0, pool) != APR_SUCCESS) {
         apr_file_printf(errfile, "%s: unable to create temporary file %s\n", 
-                        argv[0], tn);
+                        argv[0], dirname);
         exit(ERR_FILEPERM);
     }
 
     /*
      * If we're not creating a new file, copy records from the existing
      * one to the temporary file until we find the specified user.

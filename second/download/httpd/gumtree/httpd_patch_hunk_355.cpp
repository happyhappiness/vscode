      * All the file access checks (if any) have been made.  Time to go to work;
      * try to create the record for the username in question.  If that
      * fails, there's no need to waste any time on file manipulations.
      * Any error message text is returned in the record buffer, since
      * the mkrecord() routine doesn't have access to argv[].
      */
-    i = mkrecord(user, record, sizeof(record) - 1,
-                 password, alg);
-    if (i != 0) {
-        apr_file_printf(errfile, "%s: %s\n", argv[0], record);
-        exit(i);
-    }
-    if (mask & APHTP_NOFILE) {
-        printf("%s\n", record);
-        exit(0);
+    if (!(mask & APHTP_DELUSER)) {
+        i = mkrecord(user, record, sizeof(record) - 1,
+                     password, alg);
+        if (i != 0) {
+            apr_file_printf(errfile, "%s: %s\n", argv[0], record);
+            exit(i);
+        }
+        if (mask & APHTP_NOFILE) {
+            printf("%s\n", record);
+            exit(0);
+        }
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

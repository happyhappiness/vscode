 
     apr_file_printf(errfile,
     "%s -- Program to Create DBM Files for use by RewriteMap" NL
     "Usage: %s [-v] [-f format] -i SOURCE_TXT -o OUTPUT_DBM" NL
     NL
     "Options: " NL
-    " -v    More verbose output"NL
+    " -v    More verbose output" NL
     NL
-    " -i    Source Text File. If '-', use stdin."NL
+    " -i    Source Text File. If '-', use stdin." NL
     NL
-    " -o    Output DBM."NL
+    " -o    Output DBM." NL
     NL
     " -f    DBM Format.  If not specified, will use the APR Default." NL
     "           GDBM for GDBM files (%s)" NL
     "           SDBM for SDBM files (%s)" NL
     "           DB   for berkeley DB files (%s)" NL
     "           NDBM for NDBM files (%s)" NL

 }
 
 /*
  * usage info
  */
 #define NL APR_EOL_STR
-static void usage(void)
+static void usage(const char *error)
 {
-    apr_file_printf(errfile,
+    if (error) {
+    	apr_file_printf(errfile, "%s error: %s\n", shortname, error);
+    }
+	apr_file_printf(errfile,
     "%s -- program for cleaning the disk cache."                             NL
     "Usage: %s [-Dvtrn] -pPATH -lLIMIT"                                      NL
     "       %s [-nti] -dINTERVAL -pPATH -lLIMIT"                             NL
                                                                              NL
     "Options:"                                                               NL
     "  -d   Daemonize and repeat cache cleaning every INTERVAL minutes."     NL

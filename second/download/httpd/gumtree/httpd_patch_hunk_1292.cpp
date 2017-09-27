 {
     if (error) {
     	apr_file_printf(errfile, "%s error: %s\n", shortname, error);
     }
 	apr_file_printf(errfile,
     "%s -- program for cleaning the disk cache."                             NL
-    "Usage: %s [-Dvtrn] -pPATH -lLIMIT"                                      NL
-    "       %s [-nti] -dINTERVAL -pPATH -lLIMIT"                             NL
+    "Usage: %s [-Dvtrn] -pPATH -lLIMIT [-PPIDFILE]"                          NL
+    "       %s [-nti] -dINTERVAL -pPATH -lLIMIT [-PPIDFILE]"                 NL
                                                                              NL
     "Options:"                                                               NL
     "  -d   Daemonize and repeat cache cleaning every INTERVAL minutes."     NL
     "       This option is mutually exclusive with the -D, -v and -r"        NL
     "       options."                                                        NL
                                                                              NL

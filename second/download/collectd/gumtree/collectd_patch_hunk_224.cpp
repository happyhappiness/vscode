 } /* static void update_kstat (void) */
 #endif /* HAVE_LIBKSTAT */
 
 /* TODO
  * Remove all settings but `-f' and `-C'
  */
-static void exit_usage (void)
+static void exit_usage (int status)
 {
 	printf ("Usage: "PACKAGE" [OPTIONS]\n\n"
 			
 			"Available options:\n"
 			"  General:\n"
 			"    -C <file>       Configuration file.\n"

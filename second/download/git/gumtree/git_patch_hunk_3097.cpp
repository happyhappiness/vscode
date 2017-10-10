 void verify_filename(const char *prefix,
 		     const char *arg,
 		     int diagnose_misspelt_rev)
 {
 	if (*arg == '-')
 		die("bad flag '%s' used after filename", arg);
-	if (check_filename(prefix, arg))
+	if (check_filename(prefix, arg) || !no_wildcard(arg))
 		return;
 	die_verify_filename(prefix, arg, diagnose_misspelt_rev);
 }
 
 /*
  * Opposite of the above: the command line did not have -- marker

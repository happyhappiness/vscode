 
 	return ret;
 }
 
 void print_child_argv(char **cmd)
 {
-	rprintf(FINFO, "opening connection using ");
+	rprintf(FCLIENT, "opening connection using ");
 	for (; *cmd; cmd++) {
 		/* Look for characters that ought to be quoted.  This
 		* is not a great quoting algorithm, but it's
 		* sufficient for a log message. */
 		if (strspn(*cmd, "abcdefghijklmnopqrstuvwxyz"
 			   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
 			   "0123456789"
 			   ",.-_=+@/") != strlen(*cmd)) {
-			rprintf(FINFO, "\"%s\" ", *cmd);
+			rprintf(FCLIENT, "\"%s\" ", *cmd);
 		} else {
-			rprintf(FINFO, "%s ", *cmd);
+			rprintf(FCLIENT, "%s ", *cmd);
 		}
 	}
-	rprintf(FINFO, "\n");
+	rprintf(FCLIENT, "\n");
 }
 
-void out_of_memory(char *str)
+NORETURN void out_of_memory(char *str)
 {
-	rprintf(FERROR, "ERROR: out of memory in %s\n", str);
+	rprintf(FERROR, "ERROR: out of memory in %s [%s]\n", str, who_am_i());
 	exit_cleanup(RERR_MALLOC);
 }
 
-void overflow_exit(char *str)
+NORETURN void overflow_exit(char *str)
 {
-	rprintf(FERROR, "ERROR: buffer overflow in %s\n", str);
+	rprintf(FERROR, "ERROR: buffer overflow in %s [%s]\n", str, who_am_i());
 	exit_cleanup(RERR_MALLOC);
 }
 
 int set_modtime(char *fname, time_t modtime, mode_t mode)
 {
 #if !defined HAVE_LUTIMES || !defined HAVE_UTIMES

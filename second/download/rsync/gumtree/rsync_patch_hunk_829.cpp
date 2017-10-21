 		* is not a great quoting algorithm, but it's
 		* sufficient for a log message. */
 		if (strspn(*cmd, "abcdefghijklmnopqrstuvwxyz"
 			   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
 			   "0123456789"
 			   ",.-_=+@/") != strlen(*cmd)) {
-			rprintf(FINFO, "\"%s\" ", safe_fname(*cmd));
+			rprintf(FINFO, "\"%s\" ", *cmd);
 		} else {
-			rprintf(FINFO, "%s ", safe_fname(*cmd));
+			rprintf(FINFO, "%s ", *cmd);
 		}
 	}
 	rprintf(FINFO, "\n");
 }
 
-
 void out_of_memory(char *str)
 {
 	rprintf(FERROR, "ERROR: out of memory in %s\n", str);
 	exit_cleanup(RERR_MALLOC);
 }
 

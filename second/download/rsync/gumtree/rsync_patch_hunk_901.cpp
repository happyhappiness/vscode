 			rprintf(FCLIENT, "%s ", *cmd);
 		}
 	}
 	rprintf(FCLIENT, "\n");
 }
 
-NORETURN void out_of_memory(char *str)
+NORETURN void out_of_memory(const char *str)
 {
 	rprintf(FERROR, "ERROR: out of memory in %s [%s]\n", str, who_am_i());
 	exit_cleanup(RERR_MALLOC);
 }
 
-NORETURN void overflow_exit(char *str)
+NORETURN void overflow_exit(const char *str)
 {
 	rprintf(FERROR, "ERROR: buffer overflow in %s [%s]\n", str, who_am_i());
 	exit_cleanup(RERR_MALLOC);
 }
 
-int set_modtime(char *fname, time_t modtime, mode_t mode)
+int set_modtime(const char *fname, time_t modtime, mode_t mode)
 {
 #if !defined HAVE_LUTIMES || !defined HAVE_UTIMES
 	if (S_ISLNK(mode))
 		return 1;
 #endif
 

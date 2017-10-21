 			   "0123456789"
 			   ",.-_=+@/") != strlen(*cmd)) {
 			rprintf(FCLIENT, "\"%s\" ", *cmd);
 		} else {
 			rprintf(FCLIENT, "%s ", *cmd);
 		}
+		cnt++;
 	}
-	rprintf(FCLIENT, "\n");
-}
-
-NORETURN void out_of_memory(const char *str)
-{
-	rprintf(FERROR, "ERROR: out of memory in %s [%s]\n", str, who_am_i());
-	exit_cleanup(RERR_MALLOC);
-}
-
-NORETURN void overflow_exit(const char *str)
-{
-	rprintf(FERROR, "ERROR: buffer overflow in %s [%s]\n", str, who_am_i());
-	exit_cleanup(RERR_MALLOC);
+	rprintf(FCLIENT, " (%d args)\n", cnt);
 }
 
 /* This returns 0 for success, 1 for a symlink if symlink time-setting
  * is not possible, or -1 for any other error. */
-int set_modtime(const char *fname, time_t modtime, mode_t mode)
+int set_modtime(const char *fname, time_t modtime, uint32 mod_nsec, mode_t mode)
 {
 	static int switch_step = 0;
 
-	if (verbose > 2) {
+	if (DEBUG_GTE(TIME, 1)) {
 		rprintf(FINFO, "set modtime of %s to (%ld) %s",
 			fname, (long)modtime,
 			asctime(localtime(&modtime)));
 	}
 
 	switch (switch_step) {
 #ifdef HAVE_UTIMENSAT
 #include "case_N.h"
-		if (do_utimensat(fname, modtime, 0) == 0)
+		if (do_utimensat(fname, modtime, mod_nsec) == 0)
 			break;
 		if (errno != ENOSYS)
 			return -1;
 		switch_step++;
 		/* FALLTHROUGH */
 #endif
 
 #ifdef HAVE_LUTIMES
 #include "case_N.h"
-		if (do_lutimes(fname, modtime, 0) == 0)
+		if (do_lutimes(fname, modtime, mod_nsec) == 0)
 			break;
 		if (errno != ENOSYS)
 			return -1;
 		switch_step++;
 		/* FALLTHROUGH */
 #endif

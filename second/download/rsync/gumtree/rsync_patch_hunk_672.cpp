 			return -1;
 		}
 		sanitize_paths = 1;
 	}
 
 	if (am_root) {
-#ifdef HAVE_SETGROUPS
-		/* Get rid of any supplementary groups this process
-		 * might have inheristed. */
-		if (setgroups(0, NULL)) {
-			rsyserr(FERROR, errno, "setgroups failed");
-			io_printf(f_out, "@ERROR: setgroups failed\n");
-			return -1;
-		}
-#endif
-
 		/* XXXX: You could argue that if the daemon is started
 		 * by a non-root user and they explicitly specify a
 		 * gid, then we should try to change to that gid --
 		 * this could be possible if it's already in their
 		 * supplementary groups. */
 

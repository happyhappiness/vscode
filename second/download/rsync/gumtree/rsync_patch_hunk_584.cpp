 	p = lp_exclude_from(i);
 	add_exclude_file(p, 1, 0);
 
 	p = lp_exclude(i);
 	add_exclude_line(p);
 
-	log_open();
+	log_init();
 
 	if (use_chroot) {
+		/*
+		 * XXX: The 'use chroot' flag is a fairly reliable
+		 * source of confusion, because it fails under two
+		 * important circumstances: running as non-root,
+		 * running on Win32 (or possibly others).  On the
+		 * other hand, if you are running as root, then it
+		 * might be better to always use chroot.
+		 *
+		 * So, perhaps if we can't chroot we should just issue
+		 * a warning, unless a "require chroot" flag is set,
+		 * in which case we fail.
+		 */
 		if (chroot(lp_path(i))) {
-			rprintf(FERROR,"chroot %s failed\n", lp_path(i));
+			rsyserr(FERROR, errno, "chroot %s failed", lp_path(i));
 			io_printf(fd,"@ERROR: chroot failed\n");
 			return -1;
 		}
 
 		if (!push_dir("/", 0)) {
-			rprintf(FERROR,"chdir %s failed\n", lp_path(i));
+                        rsyserr(FERROR, errno, "chdir %s failed\n", lp_path(i));
 			io_printf(fd,"@ERROR: chdir failed\n");
 			return -1;
 		}
 
 	} else {
 		if (!push_dir(lp_path(i), 0)) {
-			rprintf(FERROR,"chdir %s failed\n", lp_path(i));
+			rsyserr(FERROR, errno, "chdir %s failed\n", lp_path(i));
 			io_printf(fd,"@ERROR: chdir failed\n");
 			return -1;
 		}
 		sanitize_paths = 1;
 	}
 
 	if (am_root) {
 		if (setgid(gid)) {
-			rprintf(FERROR,"setgid %d failed\n", gid);
+			rsyserr(FERROR, errno, "setgid %d failed", (int) gid);
 			io_printf(fd,"@ERROR: setgid failed\n");
 			return -1;
 		}
 
 		if (setuid(uid)) {
-			rprintf(FERROR,"setuid %d failed\n", uid);
+			rsyserr(FERROR, errno, "setuid %d failed", (int) uid);
 			io_printf(fd,"@ERROR: setuid failed\n");
 			return -1;
 		}
 
 		am_root = (getuid() == 0);
 	}

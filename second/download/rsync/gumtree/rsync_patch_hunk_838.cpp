 			rsyserr(FLOG, errno, "chroot %s failed",
 				lp_path(i));
 			io_printf(f_out, "@ERROR: chroot failed\n");
 			return -1;
 		}
 
-		if (!push_dir("/")) {
+		if (!push_dir("/", 0)) {
 			rsyserr(FLOG, errno, "chdir %s failed\n",
 				lp_path(i));
 			io_printf(f_out, "@ERROR: chdir failed\n");
 			return -1;
 		}
 
 	} else {
-		if (!push_dir(lp_path(i))) {
+		if (!push_dir(lp_path(i), 0)) {
 			rsyserr(FLOG, errno, "chdir %s failed\n",
 				lp_path(i));
 			io_printf(f_out, "@ERROR: chdir failed\n");
 			return -1;
 		}
 		sanitize_paths = 1;

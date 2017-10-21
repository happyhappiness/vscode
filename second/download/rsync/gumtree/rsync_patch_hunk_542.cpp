 		if (chroot(lp_path(i))) {
 			rprintf(FERROR,"chroot %s failed\n", lp_path(i));
 			io_printf(fd,"@ERROR: chroot failed\n");
 			return -1;
 		}
 
-		if (chdir("/")) {
+		if (!push_dir("/", 0)) {
 			rprintf(FERROR,"chdir %s failed\n", lp_path(i));
 			io_printf(fd,"@ERROR: chdir failed\n");
 			return -1;
 		}
 
-		if (setgid(gid) || getgid() != gid) {
+	} else {
+		if (!push_dir(lp_path(i), 0)) {
+			rprintf(FERROR,"chdir %s failed\n", lp_path(i));
+			io_printf(fd,"@ERROR: chdir failed\n");
+			return -1;
+		}
+	}
+
+	if (am_root) {
+		if (setgid(gid)) {
 			rprintf(FERROR,"setgid %d failed\n", gid);
 			io_printf(fd,"@ERROR: setgid failed\n");
 			return -1;
 		}
 
-		if (setuid(uid) || getuid() != uid) {
+		if (setuid(uid)) {
 			rprintf(FERROR,"setuid %d failed\n", uid);
 			io_printf(fd,"@ERROR: setuid failed\n");
 			return -1;
 		}
 
-	} else {
-		if (!push_dir(lp_path(i), 0)) {
-			rprintf(FERROR,"chdir %s failed\n", lp_path(i));
-			io_printf(fd,"@ERROR: chdir failed\n");
-			return -1;
-		}
+		am_root = (getuid() == 0);
 	}
 
-	am_root = (getuid() == 0);
-
 	io_printf(fd,"@RSYNCD: OK\n");
 
 	argv[argc++] = "rsyncd";
 
 	while (1) {
 		if (!read_line(fd, line, sizeof(line)-1)) {

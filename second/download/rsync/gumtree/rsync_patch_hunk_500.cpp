 	p = lp_exclude_from(i);
 	add_exclude_file(p, 1);
 
 	p = lp_exclude(i);
 	add_exclude_line(p);
 
+	log_open();
+
 	if (chroot(lp_path(i))) {
+		rprintf(FERROR,"chroot %s failed\n", lp_path(i));
 		io_printf(fd,"@ERROR: chroot failed\n");
 		return -1;
 	}
 
 	if (chdir("/")) {
+		rprintf(FERROR,"chdir %s failed\n", lp_path(i));
 		io_printf(fd,"@ERROR: chdir failed\n");
 		return -1;
 	}
 
-	if (setgid(gid)) {
+	if (setgid(gid) || getgid() != gid) {
+		rprintf(FERROR,"setgid %d failed\n", gid);
 		io_printf(fd,"@ERROR: setgid failed\n");
 		return -1;
 	}
 
-	if (setuid(uid)) {
+	if (setuid(uid) || getuid() != uid) {
+		rprintf(FERROR,"setuid %d failed\n", uid);
 		io_printf(fd,"@ERROR: setuid failed\n");
 		return -1;
 	}
 
 	io_printf(fd,"@RSYNCD: OK\n");
 

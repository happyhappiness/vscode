 			io_printf(fd,"@ERROR: invalid gid\n");
 			return -1;
 		} 
 		gid = atoi(p);
 	}
 
+	p = lp_exclude_from(i);
+	add_exclude_file(p, 1);
+
+	p = lp_exclude(i);
+	add_exclude_line(p);
+
 	if (chroot(lp_path(i))) {
 		io_printf(fd,"@ERROR: chroot failed\n");
 		return -1;
 	}
 
 	if (chdir("/")) {

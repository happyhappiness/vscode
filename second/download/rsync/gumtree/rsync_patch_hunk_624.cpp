 		/* TODO: Perhaps we need to document that if rsyncd is
 		 * started by somebody other than root it will inherit
 		 * all their supplementary groups. */
 
 		if (setgid(gid)) {
 			rsyserr(FERROR, errno, "setgid %d failed", (int) gid);
-			io_printf(fd,"@ERROR: setgid failed\n");
+			io_printf(f_out, "@ERROR: setgid failed\n");
 			return -1;
 		}
 
 		if (setuid(uid)) {
 			rsyserr(FERROR, errno, "setuid %d failed", (int) uid);
-			io_printf(fd,"@ERROR: setuid failed\n");
+			io_printf(f_out, "@ERROR: setuid failed\n");
 			return -1;
 		}
 
 		am_root = (getuid() == 0);
 	}
 
-	io_printf(fd,"@RSYNCD: OK\n");
+	io_printf(f_out, "@RSYNCD: OK\n");
 
 	argv[argc++] = "rsyncd";
 
 	while (1) {
-		if (!read_line(fd, line, sizeof(line)-1)) {
+		if (!read_line(f_in, line, sizeof(line)-1)) {
 			return -1;
 		}
 
 		if (!*line) break;
 
 		p = line;

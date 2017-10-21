 	io_printf(f_out, "@RSYNCD: %d\n", protocol_version);
 
 	motd = lp_motd_file();
 	if (motd && *motd) {
 		FILE *f = fopen(motd,"r");
 		while (f && !feof(f)) {
-			int len = fread(line, 1, sizeof(line)-1, f);
+			int len = fread(line, 1, sizeof line - 1, f);
 			if (len > 0) {
 				line[len] = 0;
 				io_printf(f_out, "%s", line);
 			}
 		}
-		if (f) fclose(f);
+		if (f)
+			fclose(f);
 		io_printf(f_out, "\n");
 	}
 
-	if (!read_line(f_in, line, sizeof(line)-1)) {
+	if (!read_line(f_in, line, sizeof line - 1))
 		return -1;
-	}
 
 	if (sscanf(line,"@RSYNCD: %d", &remote_protocol) != 1) {
 		io_printf(f_out, "@ERROR: protocol startup error\n");
 		return -1;
 	}
 	if (protocol_version > remote_protocol)
 		protocol_version = remote_protocol;
 
-	while (i == -1) {
-		line[0] = 0;
-		if (!read_line(f_in, line, sizeof(line)-1)) {
-			return -1;
-		}
+	line[0] = 0;
+	if (!read_line(f_in, line, sizeof line - 1))
+		return -1;
 
-		if (!*line || strcmp(line,"#list")==0) {
-			send_listing(f_out);
-			return -1;
-		}
+	if (!*line || strcmp(line, "#list") == 0) {
+		send_listing(f_out);
+		return -1;
+	}
 
-		if (*line == '#') {
-			/* it's some sort of command that I don't understand */
-			io_printf(f_out, "@ERROR: Unknown command '%s'\n", line);
-			return -1;
-		}
+	if (*line == '#') {
+		/* it's some sort of command that I don't understand */
+		io_printf(f_out, "@ERROR: Unknown command '%s'\n", line);
+		return -1;
+	}
 
-		i = lp_number(line);
-		if (i == -1) {
-			io_printf(f_out, "@ERROR: Unknown module '%s'\n", line);
-			return -1;
-		}
+	if ((i = lp_number(line)) < 0) {
+		char *addr = client_addr(f_in);
+		char *host = client_name(f_in);
+		rprintf(FLOG, "unknown module '%s' tried from %s (%s)\n",
+			line, host, addr);
+		io_printf(f_out, "@ERROR: Unknown module '%s'\n", line);
+		return -1;
 	}
 
 	return rsync_module(f_in, f_out, i);
 }
 
 

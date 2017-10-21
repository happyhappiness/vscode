 	}
 
 	if (!read_line(f_in, line, sizeof(line)-1)) {
 		return -1;
 	}
 
-	if (sscanf(line,"@RSYNCD: %d", &remote_version) != 1) {
+	if (sscanf(line,"@RSYNCD: %d", &remote_protocol) != 1) {
 		io_printf(f_out, "@ERROR: protocol startup error\n");
 		return -1;
-	}	
+	}
+	if (protocol_version > remote_protocol)
+		protocol_version = remote_protocol;
 
 	while (i == -1) {
 		line[0] = 0;
 		if (!read_line(f_in, line, sizeof(line)-1)) {
 			return -1;
 		}
 
 		if (!*line || strcmp(line,"#list")==0) {
 			send_listing(f_out);
 			return -1;
-		} 
+		}
 
 		if (*line == '#') {
 			/* it's some sort of command that I don't understand */
 			io_printf(f_out, "@ERROR: Unknown command '%s'\n", line);
 			return -1;
 		}

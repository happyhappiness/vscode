 		io_printf(f_out, "@ERROR: auth failed on module %s\n", name);
 		return -1;
 	}
 
 	module_id = i;
 
+	if (lp_read_only(i))
+		read_only = 1;
+
+	if (lp_transfer_logging(i)) {
+		if (log_format_has(lp_log_format(i), 'i'))
+			daemon_log_format_has_i = 1;
+		if (daemon_log_format_has_i
+		    || log_format_has(lp_log_format(i), 'o'))
+			daemon_log_format_has_o_or_i = 1;
+	}
+
 	am_root = (MY_UID() == 0);
 
 	if (am_root) {
 		p = lp_uid(i);
 		if (!name_to_uid(p, &uid)) {
 			if (!isdigit(*(unsigned char *)p)) {

 		die_errno("Can't dup helper output fd");
 	data->out = xfdopen(duped, "r");
 
 	write_constant(helper->in, "capabilities\n");
 
 	while (1) {
-		const char *capname;
+		const char *capname, *arg;
 		int mandatory = 0;
 		if (recvline(data, &buf))
 			exit(128);
 
 		if (!*buf.buf)
 			break;

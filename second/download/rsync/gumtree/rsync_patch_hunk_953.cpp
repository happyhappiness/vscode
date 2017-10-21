 	if (error) {
 		rprintf(FERROR, RSYNC_NAME ": getaddrinfo: %s %s: %s\n",
 			h, portbuf, gai_strerror(error));
 		return -1;
 	}
 
+	for (res = res0, addr_cnt = 0; res; res = res->ai_next, addr_cnt++) {}
+	errnos = new_array0(int, addr_cnt);
+	if (!errnos)
+		out_of_memory("open_socket_out");
+
 	s = -1;
 	/* Try to connect to all addresses for this machine until we get
 	 * through.  It might e.g. be multi-homed, or have both IPv4 and IPv6
 	 * addresses.  We need to create a socket for each record, since the
 	 * address record tells us what protocol to use to try to connect. */
-	for (res = res0; res; res = res->ai_next) {
+	for (res = res0, j = 0; res; res = res->ai_next, j++) {
 		s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
 		if (s < 0)
 			continue;
 
 		if (bind_addr
 		 && try_bind_local(s, res->ai_family, type,

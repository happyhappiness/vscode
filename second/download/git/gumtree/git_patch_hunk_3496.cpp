 	strbuf_release(&hi->hostname);
 	strbuf_release(&hi->canon_hostname);
 	strbuf_release(&hi->ip_address);
 	strbuf_release(&hi->tcp_port);
 }
 
+static void set_keep_alive(int sockfd)
+{
+	int ka = 1;
+
+	if (setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &ka, sizeof(ka)) < 0)
+		logerror("unable to set SO_KEEPALIVE on socket: %s",
+			strerror(errno));
+}
+
 static int execute(void)
 {
 	char *line = packet_buffer;
 	int pktlen, len, i;
 	char *addr = getenv("REMOTE_ADDR"), *port = getenv("REMOTE_PORT");
 	struct hostinfo hi;
 
 	hostinfo_init(&hi);
 
 	if (addr)
 		loginfo("Connection from %s:%s", addr, port);
 
+	set_keep_alive(0);
 	alarm(init_timeout ? init_timeout : timeout);
 	pktlen = packet_read(0, NULL, NULL, packet_buffer, sizeof(packet_buffer), 0);
 	alarm(0);
 
 	len = strlen(line);
 	if (pktlen != len)

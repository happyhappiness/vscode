	strbuf_release(&hi->hostname);
	strbuf_release(&hi->canon_hostname);
	strbuf_release(&hi->ip_address);
	strbuf_release(&hi->tcp_port);
}

static int execute(void)
{
	char *line = packet_buffer;
	int pktlen, len, i;
	char *addr = getenv("REMOTE_ADDR"), *port = getenv("REMOTE_PORT");
	struct hostinfo hi;

	hostinfo_init(&hi);

	if (addr)
		loginfo("Connection from %s:%s", addr, port);

	alarm(init_timeout ? init_timeout : timeout);
	pktlen = packet_read(0, NULL, NULL, packet_buffer, sizeof(packet_buffer), 0);
	alarm(0);

	len = strlen(line);
	if (pktlen != len)

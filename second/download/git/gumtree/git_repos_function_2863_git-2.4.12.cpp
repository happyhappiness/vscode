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
		loginfo("Extended attributes (%d bytes) exist <%.*s>",
			(int) pktlen - len,
			(int) pktlen - len, line + len + 1);
	if (len && line[len-1] == '\n') {
		line[--len] = 0;
		pktlen--;
	}

	if (len != pktlen)
		parse_host_arg(&hi, line + len + 1, pktlen - len - 1);

	for (i = 0; i < ARRAY_SIZE(daemon_service); i++) {
		struct daemon_service *s = &(daemon_service[i]);
		const char *arg;

		if (skip_prefix(line, "git-", &arg) &&
		    skip_prefix(arg, s->name, &arg) &&
		    *arg++ == ' ') {
			/*
			 * Note: The directory here is probably context sensitive,
			 * and might depend on the actual service being performed.
			 */
			int rc = run_service(arg, s, &hi);
			hostinfo_clear(&hi);
			return rc;
		}
	}

	hostinfo_clear(&hi);
	logerror("Protocol error: '%s'", line);
	return -1;
}
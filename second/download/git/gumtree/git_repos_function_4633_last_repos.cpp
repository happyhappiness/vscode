static enum ack_type get_ack(int fd, struct object_id *result_oid)
{
	int len;
	char *line = packet_read_line(fd, &len);
	const char *arg;

	if (!len)
		die(_("git fetch-pack: expected ACK/NAK, got EOF"));
	if (!strcmp(line, "NAK"))
		return NAK;
	if (skip_prefix(line, "ACK ", &arg)) {
		if (!get_oid_hex(arg, result_oid)) {
			arg += 40;
			len -= arg - line;
			if (len < 1)
				return ACK;
			if (strstr(arg, "continue"))
				return ACK_continue;
			if (strstr(arg, "common"))
				return ACK_common;
			if (strstr(arg, "ready"))
				return ACK_ready;
			return ACK;
		}
	}
	if (skip_prefix(line, "ERR ", &arg))
		die(_("remote error: %s"), arg);
	die(_("git fetch-pack: expected ACK/NAK, got '%s'"), line);
}
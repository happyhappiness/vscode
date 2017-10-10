				continue;
			die(_("git fetch-pack: expected shallow list"));
		}
	}
}

static enum ack_type get_ack(int fd, unsigned char *result_sha1)
{
	int len;
	char *line = packet_read_line(fd, &len);
	const char *arg;

	if (!len)
		die(_("git fetch-pack: expected ACK/NAK, got EOF"));
	if (!strcmp(line, "NAK"))
		return NAK;
	if (skip_prefix(line, "ACK ", &arg)) {
		if (!get_sha1_hex(arg, result_sha1)) {
			arg += 40;
			len -= arg - line;
			if (len < 1)
				return ACK;
			if (strstr(arg, "continue"))
				return ACK_continue;

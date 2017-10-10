}

static enum ack_type get_ack(int fd, unsigned char *result_sha1)
{
	int len;
	char *line = packet_read_line(fd, &len);

	if (!len)
		die("git fetch-pack: expected ACK/NAK, got EOF");
	if (!strcmp(line, "NAK"))
		return NAK;
	if (starts_with(line, "ACK ")) {
		if (!get_sha1_hex(line+4, result_sha1)) {
			if (len < 45)
				return ACK;
			if (strstr(line+45, "continue"))
				return ACK_continue;
			if (strstr(line+45, "common"))
				return ACK_common;
			if (strstr(line+45, "ready"))
				return ACK_ready;
			return ACK;
		}
	}
	die("git fetch_pack: expected ACK/NAK, got '%s'", line);
}

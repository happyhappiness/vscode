int packet_read(int fd, char **src_buf, size_t *src_len,
		char *buffer, unsigned size, int options)
{
	int len, ret;
	char linelen[4];

	ret = get_packet_data(fd, src_buf, src_len, linelen, 4, options);
	if (ret < 0)
		return ret;
	len = packet_length(linelen);
	if (len < 0)
		die("protocol error: bad line length character: %.4s", linelen);
	if (!len) {
		packet_trace("0000", 4, 0);
		return 0;
	}
	len -= 4;
	if (len >= size)
		die("protocol error: bad line length %d", len);
	ret = get_packet_data(fd, src_buf, src_len, buffer, len, options);
	if (ret < 0)
		return ret;

	if ((options & PACKET_READ_CHOMP_NEWLINE) &&
	    len && buffer[len-1] == '\n')
		len--;

	buffer[len] = 0;
	packet_trace(buffer, len, 0);
	return len;
}
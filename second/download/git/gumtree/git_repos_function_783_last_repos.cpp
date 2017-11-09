int packet_read_line_gently(int fd, int *dst_len, char **dst_line)
{
	int len = packet_read(fd, NULL, NULL,
			      packet_buffer, sizeof(packet_buffer),
			      PACKET_READ_CHOMP_NEWLINE|PACKET_READ_GENTLE_ON_EOF);
	if (dst_len)
		*dst_len = len;
	if (dst_line)
		*dst_line = (len > 0) ? packet_buffer : NULL;
	return len;
}
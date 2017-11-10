static char *packet_read_line_generic(int fd,
				      char **src, size_t *src_len,
				      int *dst_len)
{
	int len = packet_read(fd, src, src_len,
			      packet_buffer, sizeof(packet_buffer),
			      PACKET_READ_CHOMP_NEWLINE);
	if (dst_len)
		*dst_len = len;
	return len ? packet_buffer : NULL;
}
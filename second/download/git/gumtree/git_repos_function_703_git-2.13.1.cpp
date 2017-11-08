char *packet_read_line_buf(char **src, size_t *src_len, int *dst_len)
{
	return packet_read_line_generic(-1, src, src_len, dst_len);
}
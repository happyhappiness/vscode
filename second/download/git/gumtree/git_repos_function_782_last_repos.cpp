char *packet_read_line(int fd, int *len_p)
{
	return packet_read_line_generic(fd, NULL, NULL, len_p);
}
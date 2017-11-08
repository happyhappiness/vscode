void packet_flush(int fd)
{
	packet_trace("0000", 4, 1);
	write_or_die(fd, "0000", 4);
}
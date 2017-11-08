int packet_flush_gently(int fd)
{
	packet_trace("0000", 4, 1);
	if (write_in_full(fd, "0000", 4) == 4)
		return 0;
	return error("flush packet write failed");
}
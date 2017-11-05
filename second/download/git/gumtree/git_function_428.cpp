static int packet_write_gently(const int fd_out, const char *buf, size_t size)
{
	static char packet_write_buffer[LARGE_PACKET_MAX];
	size_t packet_size;

	if (size > sizeof(packet_write_buffer) - 4)
		return error("packet write failed - data exceeds max packet size");

	packet_trace(buf, size, 1);
	packet_size = size + 4;
	set_packet_header(packet_write_buffer, packet_size);
	memcpy(packet_write_buffer + 4, buf, size);
	if (write_in_full(fd_out, packet_write_buffer, packet_size) == packet_size)
		return 0;
	return error("packet write failed");
}
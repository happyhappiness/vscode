static ssize_t process_input(int child_fd, int band)
{
	char buf[16384];
	ssize_t sz = read(child_fd, buf, sizeof(buf));
	if (sz < 0) {
		if (errno != EAGAIN && errno != EINTR)
			error_clnt("read error: %s\n", strerror(errno));
		return sz;
	}
	send_sideband(1, band, buf, sz, LARGE_PACKET_MAX);
	return sz;
}
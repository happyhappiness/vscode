static void send_client_data(int fd, const char *data, ssize_t sz)
{
	if (use_sideband) {
		send_sideband(1, fd, data, sz, use_sideband);
		return;
	}
	if (fd == 3)
		/* emergency quit */
		fd = 2;
	if (fd == 2) {
		/* XXX: are we happy to lose stuff here? */
		xwrite(fd, data, sz);
		return;
	}
	write_or_die(fd, data, sz);
}
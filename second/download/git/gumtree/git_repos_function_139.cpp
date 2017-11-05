static ssize_t send_client_data(int fd, const char *data, ssize_t sz)
{
	if (use_sideband)
		return send_sideband(1, fd, data, sz, use_sideband);
	if (fd == 3)
		/* emergency quit */
		fd = 2;
	if (fd == 2) {
		/* XXX: are we happy to lose stuff here? */
		xwrite(fd, data, sz);
		return sz;
	}
	write_or_die(fd, data, sz);
	return sz;
}
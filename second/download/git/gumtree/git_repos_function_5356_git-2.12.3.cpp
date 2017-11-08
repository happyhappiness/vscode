static int copy_to_sideband(int in, int out, void *arg)
{
	char data[128];
	int keepalive_active = 0;

	if (keepalive_in_sec <= 0)
		use_keepalive = KEEPALIVE_NEVER;
	if (use_keepalive == KEEPALIVE_ALWAYS)
		keepalive_active = 1;

	while (1) {
		ssize_t sz;

		if (keepalive_active) {
			struct pollfd pfd;
			int ret;

			pfd.fd = in;
			pfd.events = POLLIN;
			ret = poll(&pfd, 1, 1000 * keepalive_in_sec);

			if (ret < 0) {
				if (errno == EINTR)
					continue;
				else
					break;
			} else if (ret == 0) {
				/* no data; send a keepalive packet */
				static const char buf[] = "0005\1";
				write_or_die(1, buf, sizeof(buf) - 1);
				continue;
			} /* else there is actual data to read */
		}

		sz = xread(in, data, sizeof(data));
		if (sz <= 0)
			break;

		if (use_keepalive == KEEPALIVE_AFTER_NUL && !keepalive_active) {
			const char *p = memchr(data, '\0', sz);
			if (p) {
				/*
				 * The NUL tells us to start sending keepalives. Make
				 * sure we send any other data we read along
				 * with it.
				 */
				keepalive_active = 1;
				send_sideband(1, 2, data, p - data, use_sideband);
				send_sideband(1, 2, p + 1, sz - (p - data + 1), use_sideband);
				continue;
			}
		}

		/*
		 * Either we're not looking for a NUL signal, or we didn't see
		 * it yet; just pass along the data.
		 */
		send_sideband(1, 2, data, sz, use_sideband);
	}
	close(in);
	return 0;
}
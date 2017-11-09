static int serve_cache_loop(int fd)
{
	struct pollfd pfd;
	timestamp_t wakeup;

	wakeup = check_expirations();
	if (!wakeup)
		return 0;

	pfd.fd = fd;
	pfd.events = POLLIN;
	if (poll(&pfd, 1, 1000 * wakeup) < 0) {
		if (errno != EINTR)
			die_errno("poll failed");
		return 1;
	}

	if (pfd.revents & POLLIN) {
		int client, client2;
		FILE *in, *out;

		client = accept(fd, NULL, NULL);
		if (client < 0) {
			warning_errno("accept failed");
			return 1;
		}
		client2 = dup(client);
		if (client2 < 0) {
			warning_errno("dup failed");
			close(client);
			return 1;
		}

		in = xfdopen(client, "r");
		out = xfdopen(client2, "w");
		serve_one_client(in, out);
		fclose(in);
		fclose(out);
	}
	return 1;
}
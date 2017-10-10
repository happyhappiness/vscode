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

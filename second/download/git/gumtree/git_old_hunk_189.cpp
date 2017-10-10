		packet_buf_write(&req_buf, "deepen %d", args->depth);
	packet_buf_flush(&req_buf);
	state_len = req_buf.len;

	if (args->depth > 0) {
		char *line;
		unsigned char sha1[20];

		send_request(args, fd[1], &req_buf);
		while ((line = packet_read_line(fd[0], NULL))) {
			if (starts_with(line, "shallow ")) {
				if (get_sha1_hex(line + 8, sha1))
					die("invalid shallow line: %s", line);
				register_shallow(sha1);
				continue;
			}
			if (starts_with(line, "unshallow ")) {
				if (get_sha1_hex(line + 10, sha1))
					die("invalid unshallow line: %s", line);
				if (!lookup_object(sha1))
					die("object not found: %s", line);
				/* make sure that it is parsed as shallow */
				if (!parse_object(sha1))
					die("error in object: %s", line);

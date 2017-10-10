	packet_buf_flush(&req_buf);
	state_len = req_buf.len;

	if (args->deepen) {
		char *line;
		const char *arg;
		unsigned char sha1[20];

		send_request(args, fd[1], &req_buf);
		while ((line = packet_read_line(fd[0], NULL))) {
			if (skip_prefix(line, "shallow ", &arg)) {
				if (get_sha1_hex(arg, sha1))
					die(_("invalid shallow line: %s"), line);
				register_shallow(sha1);
				continue;
			}
			if (skip_prefix(line, "unshallow ", &arg)) {
				if (get_sha1_hex(arg, sha1))
					die(_("invalid unshallow line: %s"), line);
				if (!lookup_object(sha1))
					die(_("object not found: %s"), line);
				/* make sure that it is parsed as shallow */
				if (!parse_object(sha1))
					die(_("error in object: %s"), line);
				if (unregister_shallow(sha1))
					die(_("no shallow found: %s"), line);
				continue;
			}
			die(_("expected shallow/unshallow, got %s"), line);
		}
	} else if (!args->stateless_rpc)

	}

	flushes = 0;
	retval = -1;
	while ((sha1 = get_rev())) {
		packet_buf_write(&req_buf, "have %s\n", sha1_to_hex(sha1));
		print_verbose(args, "have %s", sha1_to_hex(sha1));
		in_vain++;
		if (flush_at <= ++count) {
			int ack;

			packet_buf_flush(&req_buf);
			send_request(args, fd[1], &req_buf);

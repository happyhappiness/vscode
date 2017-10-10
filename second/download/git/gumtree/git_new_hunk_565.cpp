	int sent_ready = 0;

	save_commit_buffer = 0;

	for (;;) {
		char *line = packet_read_line(0, NULL);
		const char *arg;

		reset_timeout();

		if (!line) {
			if (multi_ack == 2 && got_common
			    && !got_other && ok_to_give_up()) {
				sent_ready = 1;
				packet_write_fmt(1, "ACK %s ready\n", last_hex);
			}
			if (have_obj.nr == 0 || multi_ack)
				packet_write_fmt(1, "NAK\n");

			if (no_done && sent_ready) {
				packet_write_fmt(1, "ACK %s\n", last_hex);
				return 0;
			}
			if (stateless_rpc)
				exit(0);
			got_common = 0;
			got_other = 0;
			continue;
		}
		if (skip_prefix(line, "have ", &arg)) {
			switch (got_sha1(arg, sha1)) {
			case -1: /* they have what we do not */
				got_other = 1;
				if (multi_ack && ok_to_give_up()) {
					const char *hex = sha1_to_hex(sha1);
					if (multi_ack == 2) {
						sent_ready = 1;
						packet_write_fmt(1, "ACK %s ready\n", hex);
					} else
						packet_write_fmt(1, "ACK %s continue\n", hex);
				}
				break;
			default:
				got_common = 1;
				memcpy(last_hex, sha1_to_hex(sha1), 41);
				if (multi_ack == 2)
					packet_write_fmt(1, "ACK %s common\n", last_hex);
				else if (multi_ack)
					packet_write_fmt(1, "ACK %s continue\n", last_hex);
				else if (have_obj.nr == 1)
					packet_write_fmt(1, "ACK %s\n", last_hex);
				break;
			}
			continue;
		}
		if (!strcmp(line, "done")) {
			if (have_obj.nr > 0) {
				if (multi_ack)
					packet_write_fmt(1, "ACK %s\n", last_hex);
				return 0;
			}
			packet_write_fmt(1, "NAK\n");
			return -1;
		}
		die("git upload-pack: expected SHA1 list, got '%s'", line);
	}
}


	} else
		chmod(final_index_name, 0444);

	if (!from_stdin) {
		printf("%s\n", sha1_to_hex(sha1));
	} else {
		struct strbuf buf = STRBUF_INIT;

		strbuf_addf(&buf, "%s\t%s\n", report, sha1_to_hex(sha1));
		write_or_die(1, buf.buf, buf.len);
		strbuf_release(&buf);

		/*
		 * Let's just mimic git-unpack-objects here and write
		 * the last part of the input buffer to stdout.
		 */
		while (input_len) {

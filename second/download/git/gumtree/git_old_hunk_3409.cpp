	args_gpg[3] = path;
	if (start_command(&gpg)) {
		unlink(path);
		return error(_("could not run gpg."));
	}

	write_in_full(gpg.in, payload, payload_size);
	close(gpg.in);

	if (gpg_output) {
		strbuf_read(gpg_output, gpg.err, 0);
		close(gpg.err);

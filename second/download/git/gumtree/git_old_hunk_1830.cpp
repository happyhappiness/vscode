			     path, strerror(errno));
	if (write_in_full(fd, signature, signature_size) < 0)
		return error(_("failed writing detached signature to '%s': %s"),
			     path, strerror(errno));
	close(fd);

	memset(&gpg, 0, sizeof(gpg));
	gpg.argv = args_gpg;
	gpg.in = -1;
	gpg.out = -1;
	if (gpg_output)
		gpg.err = -1;
	args_gpg[3] = path;

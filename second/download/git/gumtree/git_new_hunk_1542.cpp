	rc = finish_command(&po);
	if (rc) {
		/*
		 * For a normal non-zero exit, we assume pack-objects wrote
		 * something useful to stderr. For death by signal, though,
		 * we should mention it to the user. The exception is SIGPIPE
		 * (141), because that's a normal occurrence if the remote end
		 * hangs up (and we'll report that by trying to read the unpack
		 * status).
		 */
		if (rc > 128 && rc != 141)
			error("pack-objects died of signal %d", rc - 128);
		return -1;

			die("fetch-pack: unable to fork off sideband"
			    " demultiplexer");
	}
	else
		demux.out = xd[0];

	cmd.argv = argv;
	av = argv;
	*hdr_arg = 0;
	if (!args->keep_pack && unpack_limit) {
		struct pack_header header;

		if (read_pack_header(demux.out, &header))
			die("protocol error: bad pack header");
		snprintf(hdr_arg, sizeof(hdr_arg),
			 "--pack_header=%"PRIu32",%"PRIu32,
			 ntohl(header.hdr_version), ntohl(header.hdr_entries));
		if (ntohl(header.hdr_entries) < unpack_limit)
			do_keep = 0;
		else
			do_keep = 1;
	}

	if (alternate_shallow_file) {
		*av++ = "--shallow-file";
		*av++ = alternate_shallow_file;
	}

	if (do_keep) {
		if (pack_lockfile)
			cmd.out = -1;
		*av++ = cmd_name = "index-pack";
		*av++ = "--stdin";
		if (!args->quiet && !args->no_progress)
			*av++ = "-v";
		if (args->use_thin_pack)
			*av++ = "--fix-thin";
		if (args->lock_pack || unpack_limit) {
			int s = sprintf(keep_arg,
					"--keep=fetch-pack %"PRIuMAX " on ", (uintmax_t) getpid());
			if (gethostname(keep_arg + s, sizeof(keep_arg) - s))
				strcpy(keep_arg + s, "localhost");
			*av++ = keep_arg;
		}
		if (args->check_self_contained_and_connected)
			*av++ = "--check-self-contained-and-connected";
	}
	else {
		*av++ = cmd_name = "unpack-objects";
		if (args->quiet || args->no_progress)
			*av++ = "-q";
		args->check_self_contained_and_connected = 0;
	}
	if (*hdr_arg)
		*av++ = hdr_arg;
	if (fetch_fsck_objects >= 0
	    ? fetch_fsck_objects
	    : transfer_fsck_objects >= 0
	    ? transfer_fsck_objects
	    : 0)
		*av++ = "--strict";
	*av++ = NULL;

	cmd.in = demux.out;
	cmd.git_cmd = 1;
	if (start_command(&cmd))
		die("fetch-pack: unable to fork off %s", cmd_name);
	if (do_keep && pack_lockfile) {

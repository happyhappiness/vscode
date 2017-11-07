static int get_pack(struct fetch_pack_args *args,
		    int xd[2], char **pack_lockfile)
{
	struct async demux;
	int do_keep = args->keep_pack;
	const char *cmd_name;
	struct pack_header header;
	int pass_header = 0;
	struct child_process cmd = CHILD_PROCESS_INIT;
	int ret;

	memset(&demux, 0, sizeof(demux));
	if (use_sideband) {
		/* xd[] is talking with upload-pack; subprocess reads from
		 * xd[0], spits out band#2 to stderr, and feeds us band#1
		 * through demux->out.
		 */
		demux.proc = sideband_demux;
		demux.data = xd;
		demux.out = -1;
		demux.isolate_sigpipe = 1;
		if (start_async(&demux))
			die("fetch-pack: unable to fork off sideband"
			    " demultiplexer");
	}
	else
		demux.out = xd[0];

	if (!args->keep_pack && unpack_limit) {

		if (read_pack_header(demux.out, &header))
			die("protocol error: bad pack header");
		pass_header = 1;
		if (ntohl(header.hdr_entries) < unpack_limit)
			do_keep = 0;
		else
			do_keep = 1;
	}

	if (alternate_shallow_file) {
		argv_array_push(&cmd.args, "--shallow-file");
		argv_array_push(&cmd.args, alternate_shallow_file);
	}

	if (do_keep) {
		if (pack_lockfile)
			cmd.out = -1;
		cmd_name = "index-pack";
		argv_array_push(&cmd.args, cmd_name);
		argv_array_push(&cmd.args, "--stdin");
		if (!args->quiet && !args->no_progress)
			argv_array_push(&cmd.args, "-v");
		if (args->use_thin_pack)
			argv_array_push(&cmd.args, "--fix-thin");
		if (args->lock_pack || unpack_limit) {
			char hostname[256];
			if (gethostname(hostname, sizeof(hostname)))
				xsnprintf(hostname, sizeof(hostname), "localhost");
			argv_array_pushf(&cmd.args,
					"--keep=fetch-pack %"PRIuMAX " on %s",
					(uintmax_t)getpid(), hostname);
		}
		if (args->check_self_contained_and_connected)
			argv_array_push(&cmd.args, "--check-self-contained-and-connected");
	}
	else {
		cmd_name = "unpack-objects";
		argv_array_push(&cmd.args, cmd_name);
		if (args->quiet || args->no_progress)
			argv_array_push(&cmd.args, "-q");
		args->check_self_contained_and_connected = 0;
	}

	if (pass_header)
		argv_array_pushf(&cmd.args, "--pack_header=%"PRIu32",%"PRIu32,
				 ntohl(header.hdr_version),
				 ntohl(header.hdr_entries));
	if (fetch_fsck_objects >= 0
	    ? fetch_fsck_objects
	    : transfer_fsck_objects >= 0
	    ? transfer_fsck_objects
	    : 0)
		argv_array_push(&cmd.args, "--strict");

	cmd.in = demux.out;
	cmd.git_cmd = 1;
	if (start_command(&cmd))
		die("fetch-pack: unable to fork off %s", cmd_name);
	if (do_keep && pack_lockfile) {
		*pack_lockfile = index_pack_lockfile(cmd.out);
		close(cmd.out);
	}

	if (!use_sideband)
		/* Closed by start_command() */
		xd[0] = -1;

	ret = finish_command(&cmd);
	if (!ret || (args->check_self_contained_and_connected && ret == 1))
		args->self_contained_and_connected =
			args->check_self_contained_and_connected &&
			ret == 0;
	else
		die("%s failed", cmd_name);
	if (use_sideband && finish_async(&demux))
		die("error in sideband demultiplexer");
	return 0;
}
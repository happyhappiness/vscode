	struct child_process pack_objects = CHILD_PROCESS_INIT;
	char data[8193], progress[128];
	char abort_msg[] = "aborting due to possible repository "
		"corruption on the remote side.";
	int buffered = -1;
	ssize_t sz;
	const char *argv[13];
	int i, arg = 0;
	FILE *pipe_fd;

	if (shallow_nr) {
		argv[arg++] = "--shallow-file";
		argv[arg++] = "";
	}
	argv[arg++] = "pack-objects";
	argv[arg++] = "--revs";
	if (use_thin_pack)
		argv[arg++] = "--thin";

	argv[arg++] = "--stdout";
	if (shallow_nr)
		argv[arg++] = "--shallow";
	if (!no_progress)
		argv[arg++] = "--progress";
	if (use_ofs_delta)
		argv[arg++] = "--delta-base-offset";
	if (use_include_tag)
		argv[arg++] = "--include-tag";
	argv[arg++] = NULL;

	pack_objects.in = -1;
	pack_objects.out = -1;
	pack_objects.err = -1;
	pack_objects.git_cmd = 1;
	pack_objects.argv = argv;

	if (start_command(&pack_objects))
		die("git upload-pack: unable to fork git-pack-objects");

	pipe_fd = xfdopen(pack_objects.in, "w");


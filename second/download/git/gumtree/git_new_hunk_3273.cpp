	struct child_process pack_objects = CHILD_PROCESS_INIT;
	char data[8193], progress[128];
	char abort_msg[] = "aborting due to possible repository "
		"corruption on the remote side.";
	int buffered = -1;
	ssize_t sz;
	int i;
	FILE *pipe_fd;

	if (shallow_nr) {
		argv_array_push(&pack_objects.args, "--shallow-file");
		argv_array_push(&pack_objects.args, "");
	}
	argv_array_push(&pack_objects.args, "pack-objects");
	argv_array_push(&pack_objects.args, "--revs");
	if (use_thin_pack)
		argv_array_push(&pack_objects.args, "--thin");

	argv_array_push(&pack_objects.args, "--stdout");
	if (shallow_nr)
		argv_array_push(&pack_objects.args, "--shallow");
	if (!no_progress)
		argv_array_push(&pack_objects.args, "--progress");
	if (use_ofs_delta)
		argv_array_push(&pack_objects.args, "--delta-base-offset");
	if (use_include_tag)
		argv_array_push(&pack_objects.args, "--include-tag");

	pack_objects.in = -1;
	pack_objects.out = -1;
	pack_objects.err = -1;
	pack_objects.git_cmd = 1;

	if (start_command(&pack_objects))
		die("git upload-pack: unable to fork git-pack-objects");

	pipe_fd = xfdopen(pack_objects.in, "w");


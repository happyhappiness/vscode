	fd = open(filename, O_RDONLY);
	if (fd < 0)
		die_errno("unable to open %s for reading", filename);

	if (!raw && type == OBJ_TREE) {
		const char *argv[] = { "mktree", NULL };
		struct child_process cmd = CHILD_PROCESS_INIT;
		struct strbuf result = STRBUF_INIT;

		cmd.argv = argv;
		cmd.git_cmd = 1;
		cmd.in = fd;
		cmd.out = -1;

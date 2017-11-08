static int write_tar_filter_archive(const struct archiver *ar,
				    struct archiver_args *args)
{
	struct strbuf cmd = STRBUF_INIT;
	struct child_process filter = CHILD_PROCESS_INIT;
	const char *argv[2];
	int r;

	if (!ar->data)
		die("BUG: tar-filter archiver called with no filter defined");

	strbuf_addstr(&cmd, ar->data);
	if (args->compression_level >= 0)
		strbuf_addf(&cmd, " -%d", args->compression_level);

	argv[0] = cmd.buf;
	argv[1] = NULL;
	filter.argv = argv;
	filter.use_shell = 1;
	filter.in = -1;

	if (start_command(&filter) < 0)
		die_errno("unable to start '%s' filter", argv[0]);
	close(1);
	if (dup2(filter.in, 1) < 0)
		die_errno("unable to redirect descriptor");
	close(filter.in);

	r = write_tar_archive(ar, args);

	close(1);
	if (finish_command(&filter) != 0)
		die("'%s' filter reported error", argv[0]);

	strbuf_release(&cmd);
	return r;
}
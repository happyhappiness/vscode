int unbundle(struct bundle_header *header, int bundle_fd, int flags)
{
	const char *argv_index_pack[] = {"index-pack",
					 "--fix-thin", "--stdin", NULL, NULL};
	struct child_process ip = CHILD_PROCESS_INIT;

	if (flags & BUNDLE_VERBOSE)
		argv_index_pack[3] = "-v";

	if (verify_bundle(header, 0))
		return -1;
	ip.argv = argv_index_pack;
	ip.in = bundle_fd;
	ip.no_stdout = 1;
	ip.git_cmd = 1;
	if (run_command(&ip))
		return error(_("index-pack died"));
	return 0;
}
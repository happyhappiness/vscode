static int verify_one_pack(const char *path, unsigned int flags)
{
	struct child_process index_pack = CHILD_PROCESS_INIT;
	const char *argv[] = {"index-pack", NULL, NULL, NULL };
	struct strbuf arg = STRBUF_INIT;
	int verbose = flags & VERIFY_PACK_VERBOSE;
	int stat_only = flags & VERIFY_PACK_STAT_ONLY;
	int err;

	if (stat_only)
		argv[1] = "--verify-stat-only";
	else if (verbose)
		argv[1] = "--verify-stat";
	else
		argv[1] = "--verify";

	/*
	 * In addition to "foo.pack" we accept "foo.idx" and "foo";
	 * normalize these forms to "foo.pack" for "index-pack --verify".
	 */
	strbuf_addstr(&arg, path);
	if (strbuf_strip_suffix(&arg, ".idx") ||
	    !ends_with(arg.buf, ".pack"))
		strbuf_addstr(&arg, ".pack");
	argv[2] = arg.buf;

	index_pack.argv = argv;
	index_pack.git_cmd = 1;

	err = run_command(&index_pack);

	if (verbose || stat_only) {
		if (err)
			printf("%s: bad\n", arg.buf);
		else {
			if (!stat_only)
				printf("%s: ok\n", arg.buf);
		}
	}
	strbuf_release(&arg);

	return err;
}
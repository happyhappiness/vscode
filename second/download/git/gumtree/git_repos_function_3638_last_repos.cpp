static void bisect_rev_setup(struct rev_info *revs, const char *prefix,
			     const char *bad_format, const char *good_format,
			     int read_paths)
{
	struct argv_array rev_argv = ARGV_ARRAY_INIT;
	int i;

	init_revisions(revs, prefix);
	revs->abbrev = 0;
	revs->commit_format = CMIT_FMT_UNSPECIFIED;

	/* rev_argv.argv[0] will be ignored by setup_revisions */
	argv_array_push(&rev_argv, "bisect_rev_setup");
	argv_array_pushf(&rev_argv, bad_format, oid_to_hex(current_bad_oid));
	for (i = 0; i < good_revs.nr; i++)
		argv_array_pushf(&rev_argv, good_format,
				 oid_to_hex(good_revs.oid + i));
	argv_array_push(&rev_argv, "--");
	if (read_paths)
		read_bisect_paths(&rev_argv);

	setup_revisions(rev_argv.argc, rev_argv.argv, revs, NULL);
	/* XXX leak rev_argv, as "revs" may still be pointing to it */
}
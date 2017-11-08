int index_differs_from(const char *def, int diff_flags,
		       int ita_invisible_in_index)
{
	struct rev_info rev;
	struct setup_revision_opt opt;

	init_revisions(&rev, NULL);
	memset(&opt, 0, sizeof(opt));
	opt.def = def;
	setup_revisions(0, NULL, &rev, &opt);
	DIFF_OPT_SET(&rev.diffopt, QUICK);
	DIFF_OPT_SET(&rev.diffopt, EXIT_WITH_STATUS);
	rev.diffopt.flags |= diff_flags;
	rev.diffopt.ita_invisible_in_index = ita_invisible_in_index;
	run_diff_index(&rev, 1);
	if (rev.pending.alloc)
		free(rev.pending.objects);
	return (DIFF_OPT_TST(&rev.diffopt, HAS_CHANGES) != 0);
}
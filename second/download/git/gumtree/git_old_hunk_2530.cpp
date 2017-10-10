		const char *pathname, unsigned mode, int stage, void *context)
{
	printf("%s%s\n", pathname, S_ISDIR(mode) ? "/" : "");
	return 0;
}

static void show_rev_tweak_rev(struct rev_info *rev, struct setup_revision_opt *opt)
{
	if (rev->ignore_merges) {
		/* There was no "-m" on the command line */
		rev->ignore_merges = 0;
		if (!rev->first_parent_only && !rev->combine_merges) {
			/* No "--first-parent", "-c", or "--cc" */

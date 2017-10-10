	 */
	if (revs->reverse && revs->graph)
		die("cannot combine --reverse with --graph");

	if (revs->reflog_info && revs->graph)
		die("cannot combine --walk-reflogs with --graph");
	if (!revs->reflog_info && revs->grep_filter.use_reflog_filter)
		die("cannot use --grep-reflog without --walk-reflogs");

	return left;
}

static void add_child(struct rev_info *revs, struct commit *parent, struct commit *child)
{
	struct commit_list *l = xcalloc(1, sizeof(*l));

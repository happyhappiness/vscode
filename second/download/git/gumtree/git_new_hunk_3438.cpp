	if (!revs->reflog_info && revs->grep_filter.use_reflog_filter)
		die("cannot use --grep-reflog without --walk-reflogs");

	if (revs->first_parent_only && revs->bisect)
		die(_("--first-parent is incompatible with --bisect"));

	if (revs->expand_tabs_in_log < 0)
		revs->expand_tabs_in_log = revs->expand_tabs_in_log_default;

	return left;
}

static void add_child(struct rev_info *revs, struct commit *parent, struct commit *child)
{
	struct commit_list *l = xcalloc(1, sizeof(*l));

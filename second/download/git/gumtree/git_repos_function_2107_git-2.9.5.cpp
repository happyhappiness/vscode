static void skip_uninteresting(struct tree_desc *t, struct strbuf *base,
			       struct diff_options *opt)
{
	enum interesting match;

	while (t->size) {
		match = tree_entry_interesting(&t->entry, base, 0, &opt->pathspec);
		if (match) {
			if (match == all_entries_not_interesting)
				t->size = 0;
			break;
		}
		update_tree_entry(t);
	}
}
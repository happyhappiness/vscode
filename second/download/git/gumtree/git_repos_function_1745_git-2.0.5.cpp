static void show_tree(struct diff_options *opt, const char *prefix,
		      struct tree_desc *desc, struct strbuf *base)
{
	enum interesting match = entry_not_interesting;
	for (; desc->size; update_tree_entry(desc)) {
		if (match != all_entries_interesting) {
			match = tree_entry_interesting(&desc->entry, base, 0,
						       &opt->pathspec);
			if (match == all_entries_not_interesting)
				break;
			if (match == entry_not_interesting)
				continue;
		}
		show_entry(opt, prefix, desc, base);
	}
}
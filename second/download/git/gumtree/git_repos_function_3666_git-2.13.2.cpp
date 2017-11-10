static struct string_list *get_renames(struct merge_options *o,
				       struct tree *tree,
				       struct tree *o_tree,
				       struct tree *a_tree,
				       struct tree *b_tree,
				       struct string_list *entries)
{
	int i;
	struct string_list *renames;
	struct diff_options opts;

	renames = xcalloc(1, sizeof(struct string_list));
	if (!o->detect_rename)
		return renames;

	diff_setup(&opts);
	DIFF_OPT_SET(&opts, RECURSIVE);
	DIFF_OPT_CLR(&opts, RENAME_EMPTY);
	opts.detect_rename = DIFF_DETECT_RENAME;
	opts.rename_limit = o->merge_rename_limit >= 0 ? o->merge_rename_limit :
			    o->diff_rename_limit >= 0 ? o->diff_rename_limit :
			    1000;
	opts.rename_score = o->rename_score;
	opts.show_rename_progress = o->show_rename_progress;
	opts.output_format = DIFF_FORMAT_NO_OUTPUT;
	diff_setup_done(&opts);
	diff_tree_sha1(o_tree->object.oid.hash, tree->object.oid.hash, "", &opts);
	diffcore_std(&opts);
	if (opts.needed_rename_limit > o->needed_rename_limit)
		o->needed_rename_limit = opts.needed_rename_limit;
	for (i = 0; i < diff_queued_diff.nr; ++i) {
		struct string_list_item *item;
		struct rename *re;
		struct diff_filepair *pair = diff_queued_diff.queue[i];
		if (pair->status != 'R') {
			diff_free_filepair(pair);
			continue;
		}
		re = xmalloc(sizeof(*re));
		re->processed = 0;
		re->pair = pair;
		item = string_list_lookup(entries, re->pair->one->path);
		if (!item)
			re->src_entry = insert_stage_data(re->pair->one->path,
					o_tree, a_tree, b_tree, entries);
		else
			re->src_entry = item->util;

		item = string_list_lookup(entries, re->pair->two->path);
		if (!item)
			re->dst_entry = insert_stage_data(re->pair->two->path,
					o_tree, a_tree, b_tree, entries);
		else
			re->dst_entry = item->util;
		item = string_list_insert(renames, pair->one->path);
		item->util = re;
	}
	opts.output_format = DIFF_FORMAT_NO_OUTPUT;
	diff_queued_diff.nr = 0;
	diff_flush(&opts);
	return renames;
}
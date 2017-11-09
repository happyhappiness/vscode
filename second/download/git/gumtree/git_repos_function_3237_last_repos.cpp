int unpack_trees(unsigned len, struct tree_desc *t, struct unpack_trees_options *o)
{
	int i, ret;
	static struct cache_entry *dfc;
	struct exclude_list el;

	if (len > MAX_UNPACK_TREES)
		die("unpack_trees takes at most %d trees", MAX_UNPACK_TREES);

	memset(&el, 0, sizeof(el));
	if (!core_apply_sparse_checkout || !o->update)
		o->skip_sparse_checkout = 1;
	if (!o->skip_sparse_checkout) {
		char *sparse = git_pathdup("info/sparse-checkout");
		if (add_excludes_from_file_to_list(sparse, "", 0, &el, NULL) < 0)
			o->skip_sparse_checkout = 1;
		else
			o->el = &el;
		free(sparse);
	}

	memset(&o->result, 0, sizeof(o->result));
	o->result.initialized = 1;
	o->result.timestamp.sec = o->src_index->timestamp.sec;
	o->result.timestamp.nsec = o->src_index->timestamp.nsec;
	o->result.version = o->src_index->version;
	o->result.split_index = o->src_index->split_index;
	if (o->result.split_index)
		o->result.split_index->refcount++;
	hashcpy(o->result.sha1, o->src_index->sha1);
	o->merge_size = len;
	mark_all_ce_unused(o->src_index);

	/*
	 * Sparse checkout loop #1: set NEW_SKIP_WORKTREE on existing entries
	 */
	if (!o->skip_sparse_checkout)
		mark_new_skip_worktree(o->el, o->src_index, 0, CE_NEW_SKIP_WORKTREE);

	if (!dfc)
		dfc = xcalloc(1, cache_entry_size(0));
	o->df_conflict_entry = dfc;

	if (len) {
		const char *prefix = o->prefix ? o->prefix : "";
		struct traverse_info info;

		setup_traverse_info(&info, prefix);
		info.fn = unpack_callback;
		info.data = o;
		info.show_all_errors = o->show_all_errors;
		info.pathspec = o->pathspec;

		if (o->prefix) {
			/*
			 * Unpack existing index entries that sort before the
			 * prefix the tree is spliced into.  Note that o->merge
			 * is always true in this case.
			 */
			while (1) {
				struct cache_entry *ce = next_cache_entry(o);
				if (!ce)
					break;
				if (ce_in_traverse_path(ce, &info))
					break;
				if (unpack_index_entry(ce, o) < 0)
					goto return_failed;
			}
		}

		if (traverse_trees(len, t, &info) < 0)
			goto return_failed;
	}

	/* Any left-over entries in the index? */
	if (o->merge) {
		while (1) {
			struct cache_entry *ce = next_cache_entry(o);
			if (!ce)
				break;
			if (unpack_index_entry(ce, o) < 0)
				goto return_failed;
		}
	}
	mark_all_ce_unused(o->src_index);

	if (o->trivial_merges_only && o->nontrivial_merge) {
		ret = unpack_failed(o, "Merge requires file-level merging");
		goto done;
	}

	if (!o->skip_sparse_checkout) {
		int empty_worktree = 1;

		/*
		 * Sparse checkout loop #2: set NEW_SKIP_WORKTREE on entries not in loop #1
		 * If the will have NEW_SKIP_WORKTREE, also set CE_SKIP_WORKTREE
		 * so apply_sparse_checkout() won't attempt to remove it from worktree
		 */
		mark_new_skip_worktree(o->el, &o->result, CE_ADDED, CE_SKIP_WORKTREE | CE_NEW_SKIP_WORKTREE);

		ret = 0;
		for (i = 0; i < o->result.cache_nr; i++) {
			struct cache_entry *ce = o->result.cache[i];

			/*
			 * Entries marked with CE_ADDED in merged_entry() do not have
			 * verify_absent() check (the check is effectively disabled
			 * because CE_NEW_SKIP_WORKTREE is set unconditionally).
			 *
			 * Do the real check now because we have had
			 * correct CE_NEW_SKIP_WORKTREE
			 */
			if (ce->ce_flags & CE_ADDED &&
			    verify_absent(ce, ERROR_WOULD_LOSE_UNTRACKED_OVERWRITTEN, o)) {
				if (!o->show_all_errors)
					goto return_failed;
				ret = -1;
			}

			if (apply_sparse_checkout(&o->result, ce, o)) {
				if (!o->show_all_errors)
					goto return_failed;
				ret = -1;
			}
			if (!ce_skip_worktree(ce))
				empty_worktree = 0;

		}
		if (ret < 0)
			goto return_failed;
		/*
		 * Sparse checkout is meant to narrow down checkout area
		 * but it does not make sense to narrow down to empty working
		 * tree. This is usually a mistake in sparse checkout rules.
		 * Do not allow users to do that.
		 */
		if (o->result.cache_nr && empty_worktree) {
			ret = unpack_failed(o, "Sparse checkout leaves no entry on working directory");
			goto done;
		}
	}

	o->src_index = NULL;
	ret = check_updates(o) ? (-2) : 0;
	if (o->dst_index) {
		if (!ret) {
			if (!o->result.cache_tree)
				o->result.cache_tree = cache_tree();
			if (!cache_tree_fully_valid(o->result.cache_tree))
				cache_tree_update(&o->result,
						  WRITE_TREE_SILENT |
						  WRITE_TREE_REPAIR);
		}
		move_index_extensions(&o->result, o->dst_index);
		discard_index(o->dst_index);
		*o->dst_index = o->result;
	} else {
		discard_index(&o->result);
	}

done:
	clear_exclude_list(&el);
	return ret;

return_failed:
	if (o->show_all_errors)
		display_error_msgs(o);
	mark_all_ce_unused(o->src_index);
	ret = unpack_failed(o, NULL);
	if (o->exiting_early)
		ret = 0;
	goto done;
}
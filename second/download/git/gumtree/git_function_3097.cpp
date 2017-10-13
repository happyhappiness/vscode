static int merge_working_tree(const struct checkout_opts *opts,
			      struct branch_info *old,
			      struct branch_info *new,
			      int *writeout_error)
{
	int ret;
	struct lock_file *lock_file = xcalloc(1, sizeof(struct lock_file));

	hold_locked_index(lock_file, 1);
	if (read_cache_preload(NULL) < 0)
		return error(_("corrupt index file"));

	resolve_undo_clear();
	if (opts->force) {
		ret = reset_tree(new->commit->tree, opts, 1, writeout_error);
		if (ret)
			return ret;
	} else {
		struct tree_desc trees[2];
		struct tree *tree;
		struct unpack_trees_options topts;

		memset(&topts, 0, sizeof(topts));
		topts.head_idx = -1;
		topts.src_index = &the_index;
		topts.dst_index = &the_index;

		setup_unpack_trees_porcelain(&topts, "checkout");

		refresh_cache(REFRESH_QUIET);

		if (unmerged_cache()) {
			error(_("you need to resolve your current index first"));
			return 1;
		}

		/* 2-way merge to the new branch */
		topts.initial_checkout = is_cache_unborn();
		topts.update = 1;
		topts.merge = 1;
		topts.gently = opts->merge && old->commit;
		topts.verbose_update = opts->show_progress;
		topts.fn = twoway_merge;
		if (opts->overwrite_ignore) {
			topts.dir = xcalloc(1, sizeof(*topts.dir));
			topts.dir->flags |= DIR_SHOW_IGNORED;
			setup_standard_excludes(topts.dir);
		}
		tree = parse_tree_indirect(old->commit ?
					   old->commit->object.oid.hash :
					   EMPTY_TREE_SHA1_BIN);
		init_tree_desc(&trees[0], tree->buffer, tree->size);
		tree = parse_tree_indirect(new->commit->object.oid.hash);
		init_tree_desc(&trees[1], tree->buffer, tree->size);

		ret = unpack_trees(2, trees, &topts);
		if (ret == -1) {
			/*
			 * Unpack couldn't do a trivial merge; either
			 * give up or do a real merge, depending on
			 * whether the merge flag was used.
			 */
			struct tree *result;
			struct tree *work;
			struct merge_options o;
			if (!opts->merge)
				return 1;

			/*
			 * Without old->commit, the below is the same as
			 * the two-tree unpack we already tried and failed.
			 */
			if (!old->commit)
				return 1;

			/* Do more real merge */

			/*
			 * We update the index fully, then write the
			 * tree from the index, then merge the new
			 * branch with the current tree, with the old
			 * branch as the base. Then we reset the index
			 * (but not the working tree) to the new
			 * branch, leaving the working tree as the
			 * merged version, but skipping unmerged
			 * entries in the index.
			 */

			add_files_to_cache(NULL, NULL, 0, 0);
			/*
			 * NEEDSWORK: carrying over local changes
			 * when branches have different end-of-line
			 * normalization (or clean+smudge rules) is
			 * a pain; plumb in an option to set
			 * o.renormalize?
			 */
			init_merge_options(&o);
			o.verbosity = 0;
			work = write_tree_from_memory(&o);

			ret = reset_tree(new->commit->tree, opts, 1,
					 writeout_error);
			if (ret)
				return ret;
			o.ancestor = old->name;
			o.branch1 = new->name;
			o.branch2 = "local";
			merge_trees(&o, new->commit->tree, work,
				old->commit->tree, &result);
			ret = reset_tree(new->commit->tree, opts, 0,
					 writeout_error);
			if (ret)
				return ret;
		}
	}

	if (!active_cache_tree)
		active_cache_tree = cache_tree();

	if (!cache_tree_fully_valid(active_cache_tree))
		cache_tree_update(&the_index, WRITE_TREE_SILENT | WRITE_TREE_REPAIR);

	if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
		die(_("unable to write new index file"));

	if (!opts->force && !opts->quiet)
		show_local_changes(&new->commit->object, &opts->diff_options);

	return 0;
}
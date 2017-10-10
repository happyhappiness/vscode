	}
	if (unpack_trees(nr_trees, t, &opts))
		return -1;
	return 0;
}

static void write_tree_trivial(struct object_id *oid)
{
	if (write_cache_as_tree(oid->hash, 0, NULL))
		die(_("git write-tree failed to write a tree"));
}

static int try_merge_strategy(const char *strategy, struct commit_list *common,
			      struct commit_list *remoteheads,
			      struct commit *head)
{
	static struct lock_file lock;
	const char *head_arg = "HEAD";

	hold_locked_index(&lock, LOCK_DIE_ON_ERROR);
	refresh_cache(REFRESH_QUIET);
	if (active_cache_changed &&
	    write_locked_index(&the_index, &lock, COMMIT_LOCK))
		return error(_("Unable to write index."));

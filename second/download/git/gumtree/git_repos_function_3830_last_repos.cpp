int merge_recursive_generic(struct merge_options *o,
			    const struct object_id *head,
			    const struct object_id *merge,
			    int num_base_list,
			    const struct object_id **base_list,
			    struct commit **result)
{
	int clean;
	struct lock_file *lock = xcalloc(1, sizeof(struct lock_file));
	struct commit *head_commit = get_ref(head, o->branch1);
	struct commit *next_commit = get_ref(merge, o->branch2);
	struct commit_list *ca = NULL;

	if (base_list) {
		int i;
		for (i = 0; i < num_base_list; ++i) {
			struct commit *base;
			if (!(base = get_ref(base_list[i], oid_to_hex(base_list[i]))))
				return err(o, _("Could not parse object '%s'"),
					oid_to_hex(base_list[i]));
			commit_list_insert(base, &ca);
		}
	}

	hold_locked_index(lock, LOCK_DIE_ON_ERROR);
	clean = merge_recursive(o, head_commit, next_commit, ca,
			result);
	if (clean < 0)
		return clean;

	if (active_cache_changed &&
	    write_locked_index(&the_index, lock, COMMIT_LOCK))
		return err(o, _("Unable to write index."));

	return clean ? 0 : 1;
}
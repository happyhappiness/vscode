	for (iter = ca; iter; iter = iter->next) {
		const char *saved_b1, *saved_b2;
		o->call_depth++;
		/*
		 * When the merge fails, the result contains files
		 * with conflict markers. The cleanness flag is
		 * ignored, it was never actually used, as result of
		 * merge_trees has always overwritten it: the committed
		 * "conflicts" were already resolved.
		 */
		discard_cache();
		saved_b1 = o->branch1;
		saved_b2 = o->branch2;
		o->branch1 = "Temporary merge branch 1";
		o->branch2 = "Temporary merge branch 2";
		merge_recursive(o, merged_common_ancestors, iter->item,
				NULL, &merged_common_ancestors);
		o->branch1 = saved_b1;
		o->branch2 = saved_b2;
		o->call_depth--;

		if (!merged_common_ancestors)
			die(_("merge returned no commit"));
	}

	discard_cache();
	if (!o->call_depth)
		read_cache();

	o->ancestor = "merged common ancestors";
	clean = merge_trees(o, h1->tree, h2->tree, merged_common_ancestors->tree,
			    &mrtree);

	if (o->call_depth) {
		*result = make_virtual_commit(mrtree, "merged tree");
		commit_list_insert(h1, &(*result)->parents);
		commit_list_insert(h2, &(*result)->parents->next);
	}
	flush_output(o);
	if (show(o, 2))
		diff_warn_rename_limit("merge.renamelimit",
				       o->needed_rename_limit, 0);
	return clean;
}

static struct commit *get_ref(const unsigned char *sha1, const char *name)
{
	struct object *object;

	object = deref_tag(parse_object(sha1), name, strlen(name));
	if (!object)
		return NULL;
	if (object->type == OBJ_TREE)
		return make_virtual_commit((struct tree*)object, name);
	if (object->type != OBJ_COMMIT)
		return NULL;
	if (parse_commit((struct commit *)object))
		return NULL;
	return (struct commit *)object;
}

int merge_recursive_generic(struct merge_options *o,
			    const unsigned char *head,
			    const unsigned char *merge,
			    int num_base_list,
			    const unsigned char **base_list,
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
			if (!(base = get_ref(base_list[i], sha1_to_hex(base_list[i]))))
				return error(_("Could not parse object '%s'"),
					sha1_to_hex(base_list[i]));
			commit_list_insert(base, &ca);
		}
	}

	hold_locked_index(lock, 1);
	clean = merge_recursive(o, head_commit, next_commit, ca,
			result);
	if (active_cache_changed &&
	    write_locked_index(&the_index, lock, COMMIT_LOCK))
		return error(_("Unable to write index."));

	return clean ? 0 : 1;
}

static void merge_recursive_config(struct merge_options *o)
{

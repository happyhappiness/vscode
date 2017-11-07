void traverse_commit_list(struct rev_info *revs,
			  show_commit_fn show_commit,
			  show_object_fn show_object,
			  void *data)
{
	int i;
	struct commit *commit;
	struct strbuf base;

	strbuf_init(&base, PATH_MAX);
	while ((commit = get_revision(revs)) != NULL) {
		/*
		 * an uninteresting boundary commit may not have its tree
		 * parsed yet, but we are not going to show them anyway
		 */
		if (commit->tree)
			add_pending_tree(revs, commit->tree);
		show_commit(commit, data);
	}
	for (i = 0; i < revs->pending.nr; i++) {
		struct object_array_entry *pending = revs->pending.objects + i;
		struct object *obj = pending->item;
		const char *name = pending->name;
		if (obj->flags & (UNINTERESTING | SEEN))
			continue;
		if (obj->type == OBJ_TAG) {
			obj->flags |= SEEN;
			show_object(obj, NULL, name, data);
			continue;
		}
		if (obj->type == OBJ_TREE) {
			process_tree(revs, (struct tree *)obj, show_object,
				     NULL, &base, name, data);
			continue;
		}
		if (obj->type == OBJ_BLOB) {
			process_blob(revs, (struct blob *)obj, show_object,
				     NULL, name, data);
			continue;
		}
		die("unknown pending object %s (%s)",
		    sha1_to_hex(obj->sha1), name);
	}
	if (revs->pending.nr) {
		free(revs->pending.objects);
		revs->pending.nr = 0;
		revs->pending.alloc = 0;
		revs->pending.objects = NULL;
	}
	strbuf_release(&base);
}
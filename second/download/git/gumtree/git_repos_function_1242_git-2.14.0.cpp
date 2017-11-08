static int add_parents_only(struct rev_info *revs, const char *arg_, int flags,
			    int exclude_parent)
{
	struct object_id oid;
	struct object *it;
	struct commit *commit;
	struct commit_list *parents;
	int parent_number;
	const char *arg = arg_;

	if (*arg == '^') {
		flags ^= UNINTERESTING | BOTTOM;
		arg++;
	}
	if (get_sha1_committish(arg, oid.hash))
		return 0;
	while (1) {
		it = get_reference(revs, arg, &oid, 0);
		if (!it && revs->ignore_missing)
			return 0;
		if (it->type != OBJ_TAG)
			break;
		if (!((struct tag*)it)->tagged)
			return 0;
		oidcpy(&oid, &((struct tag*)it)->tagged->oid);
	}
	if (it->type != OBJ_COMMIT)
		return 0;
	commit = (struct commit *)it;
	if (exclude_parent &&
	    exclude_parent > commit_list_count(commit->parents))
		return 0;
	for (parents = commit->parents, parent_number = 1;
	     parents;
	     parents = parents->next, parent_number++) {
		if (exclude_parent && parent_number != exclude_parent)
			continue;

		it = &parents->item->object;
		it->flags |= flags;
		add_rev_cmdline(revs, it, arg_, REV_CMD_PARENTS_ONLY, flags);
		add_pending_object(revs, it, arg);
	}
	return 1;
}
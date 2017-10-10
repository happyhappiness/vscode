	else if (strcmp(arg, "none"))
		die("bad --ignore-submodules argument: %s", arg);
}

static int prepare_submodule_summary(struct rev_info *rev, const char *path,
		struct commit *left, struct commit *right,
		struct commit_list *merge_bases)
{
	struct commit_list *list;

	init_revisions(rev, NULL);
	setup_revisions(0, NULL, rev, NULL);
	rev->left_right = 1;
	rev->first_parent_only = 1;
	left->object.flags |= SYMMETRIC_LEFT;
	add_pending_object(rev, &left->object, path);
	add_pending_object(rev, &right->object, path);
	for (list = merge_bases; list; list = list->next) {
		list->item->object.flags |= UNINTERESTING;
		add_pending_object(rev, &list->item->object,
			oid_to_hex(&list->item->object.oid));
	}
	return prepare_revision_walk(rev);

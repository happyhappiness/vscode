static int prepare_submodule_summary(struct rev_info *rev, const char *path,
		struct commit *left, struct commit *right,
		int *fast_forward, int *fast_backward)
{
	struct commit_list *merge_bases, *list;

	init_revisions(rev, NULL);
	setup_revisions(0, NULL, rev, NULL);
	rev->left_right = 1;
	rev->first_parent_only = 1;
	left->object.flags |= SYMMETRIC_LEFT;
	add_pending_object(rev, &left->object, path);
	add_pending_object(rev, &right->object, path);
	merge_bases = get_merge_bases(left, right, 1);
	if (merge_bases) {
		if (merge_bases->item == left)
			*fast_forward = 1;
		else if (merge_bases->item == right)
			*fast_backward = 1;
	}
	for (list = merge_bases; list; list = list->next) {
		list->item->object.flags |= UNINTERESTING;
		add_pending_object(rev, &list->item->object,
			sha1_to_hex(list->item->object.sha1));
	}
	return prepare_revision_walk(rev);
}
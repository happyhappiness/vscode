static void show_detached(struct ref_list *ref_list)
{
	struct commit *head_commit = lookup_commit_reference_gently(head_sha1, 1);

	if (head_commit && is_descendant_of(head_commit, ref_list->with_commit)) {
		struct ref_item item;
		item.name = get_head_description();
		item.width = utf8_strwidth(item.name);
		item.kind = REF_LOCAL_BRANCH;
		item.dest = NULL;
		item.commit = head_commit;
		item.ignore = 0;
		if (item.width > ref_list->maxwidth)
			ref_list->maxwidth = item.width;
		print_ref_item(&item, ref_list->maxwidth, ref_list->verbose, ref_list->abbrev, 1, "");
		free(item.name);
	}
}
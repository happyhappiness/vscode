static void add_missing_tags(struct ref *src, struct ref **dst, struct ref ***dst_tail)
{
	struct string_list dst_tag = STRING_LIST_INIT_NODUP;
	struct string_list src_tag = STRING_LIST_INIT_NODUP;
	struct string_list_item *item;
	struct ref *ref;
	struct tips sent_tips;

	/*
	 * Collect everything we know they would have at the end of
	 * this push, and collect all tags they have.
	 */
	memset(&sent_tips, 0, sizeof(sent_tips));
	for (ref = *dst; ref; ref = ref->next) {
		if (ref->peer_ref &&
		    !is_null_oid(&ref->peer_ref->new_oid))
			add_to_tips(&sent_tips, &ref->peer_ref->new_oid);
		else
			add_to_tips(&sent_tips, &ref->old_oid);
		if (starts_with(ref->name, "refs/tags/"))
			string_list_append(&dst_tag, ref->name);
	}
	clear_commit_marks_many(sent_tips.nr, sent_tips.tip, TMP_MARK);

	string_list_sort(&dst_tag);

	/* Collect tags they do not have. */
	for (ref = src; ref; ref = ref->next) {
		if (!starts_with(ref->name, "refs/tags/"))
			continue; /* not a tag */
		if (string_list_has_string(&dst_tag, ref->name))
			continue; /* they already have it */
		if (sha1_object_info(ref->new_oid.hash, NULL) != OBJ_TAG)
			continue; /* be conservative */
		item = string_list_append(&src_tag, ref->name);
		item->util = ref;
	}
	string_list_clear(&dst_tag, 0);

	/*
	 * At this point, src_tag lists tags that are missing from
	 * dst, and sent_tips lists the tips we are pushing or those
	 * that we know they already have. An element in the src_tag
	 * that is an ancestor of any of the sent_tips needs to be
	 * sent to the other side.
	 */
	if (sent_tips.nr) {
		for_each_string_list_item(item, &src_tag) {
			struct ref *ref = item->util;
			struct ref *dst_ref;
			struct commit *commit;

			if (is_null_oid(&ref->new_oid))
				continue;
			commit = lookup_commit_reference_gently(ref->new_oid.hash, 1);
			if (!commit)
				/* not pushing a commit, which is not an error */
				continue;

			/*
			 * Is this tag, which they do not have, reachable from
			 * any of the commits we are sending?
			 */
			if (!in_merge_bases_many(commit, sent_tips.nr, sent_tips.tip))
				continue;

			/* Add it in */
			dst_ref = make_linked_ref(ref->name, dst_tail);
			oidcpy(&dst_ref->new_oid, &ref->new_oid);
			dst_ref->peer_ref = copy_ref(ref);
		}
	}
	string_list_clear(&src_tag, 0);
	free(sent_tips.tip);
}
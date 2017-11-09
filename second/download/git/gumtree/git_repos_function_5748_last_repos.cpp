static void find_non_local_tags(struct transport *transport,
			struct ref **head,
			struct ref ***tail)
{
	struct string_list existing_refs = STRING_LIST_INIT_DUP;
	struct string_list remote_refs = STRING_LIST_INIT_NODUP;
	const struct ref *ref;
	struct string_list_item *item = NULL;

	for_each_ref(add_existing, &existing_refs);
	for (ref = transport_get_remote_refs(transport); ref; ref = ref->next) {
		if (!starts_with(ref->name, "refs/tags/"))
			continue;

		/*
		 * The peeled ref always follows the matching base
		 * ref, so if we see a peeled ref that we don't want
		 * to fetch then we can mark the ref entry in the list
		 * as one to ignore by setting util to NULL.
		 */
		if (ends_with(ref->name, "^{}")) {
			if (item &&
			    !has_object_file_with_flags(&ref->old_oid,
							OBJECT_INFO_QUICK) &&
			    !will_fetch(head, ref->old_oid.hash) &&
			    !has_sha1_file_with_flags(item->util,
						      OBJECT_INFO_QUICK) &&
			    !will_fetch(head, item->util))
				item->util = NULL;
			item = NULL;
			continue;
		}

		/*
		 * If item is non-NULL here, then we previously saw a
		 * ref not followed by a peeled reference, so we need
		 * to check if it is a lightweight tag that we want to
		 * fetch.
		 */
		if (item &&
		    !has_sha1_file_with_flags(item->util, OBJECT_INFO_QUICK) &&
		    !will_fetch(head, item->util))
			item->util = NULL;

		item = NULL;

		/* skip duplicates and refs that we already have */
		if (string_list_has_string(&remote_refs, ref->name) ||
		    string_list_has_string(&existing_refs, ref->name))
			continue;

		item = string_list_insert(&remote_refs, ref->name);
		item->util = (void *)&ref->old_oid;
	}
	string_list_clear(&existing_refs, 1);

	/*
	 * We may have a final lightweight tag that needs to be
	 * checked to see if it needs fetching.
	 */
	if (item &&
	    !has_sha1_file_with_flags(item->util, OBJECT_INFO_QUICK) &&
	    !will_fetch(head, item->util))
		item->util = NULL;

	/*
	 * For all the tags in the remote_refs string list,
	 * add them to the list of refs to be fetched
	 */
	for_each_string_list_item(item, &remote_refs) {
		/* Unless we have already decided to ignore this item... */
		if (item->util)
		{
			struct ref *rm = alloc_ref(item->string);
			rm->peer_ref = alloc_ref(item->string);
			oidcpy(&rm->old_oid, item->util);
			**tail = rm;
			*tail = &rm->next;
		}
	}

	string_list_clear(&remote_refs, 0);
}
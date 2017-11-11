static int do_fetch(struct transport *transport,
		    struct refspec *refs, int ref_count)
{
	struct string_list existing_refs = STRING_LIST_INIT_DUP;
	struct ref *ref_map;
	struct ref *rm;
	int autotags = (transport->remote->fetch_tags == 1);
	int retcode = 0;

	for_each_ref(add_existing, &existing_refs);

	if (tags == TAGS_DEFAULT) {
		if (transport->remote->fetch_tags == 2)
			tags = TAGS_SET;
		if (transport->remote->fetch_tags == -1)
			tags = TAGS_UNSET;
	}

	if (!transport->get_refs_list || !transport->fetch)
		die(_("Don't know how to fetch from %s"), transport->url);

	/* if not appending, truncate FETCH_HEAD */
	if (!append && !dry_run) {
		retcode = truncate_fetch_head();
		if (retcode)
			goto cleanup;
	}

	ref_map = get_ref_map(transport, refs, ref_count, tags, &autotags);
	if (!update_head_ok)
		check_not_current_branch(ref_map);

	for (rm = ref_map; rm; rm = rm->next) {
		if (rm->peer_ref) {
			struct string_list_item *peer_item =
				string_list_lookup(&existing_refs,
						   rm->peer_ref->name);
			if (peer_item) {
				struct object_id *old_oid = peer_item->util;
				oidcpy(&rm->peer_ref->old_oid, old_oid);
			}
		}
	}

	if (tags == TAGS_DEFAULT && autotags)
		transport_set_option(transport, TRANS_OPT_FOLLOWTAGS, "1");
	if (prune) {
		/*
		 * We only prune based on refspecs specified
		 * explicitly (via command line or configuration); we
		 * don't care whether --tags was specified.
		 */
		if (ref_count) {
			prune_refs(refs, ref_count, ref_map, transport->url);
		} else {
			prune_refs(transport->remote->fetch,
				   transport->remote->fetch_refspec_nr,
				   ref_map,
				   transport->url);
		}
	}
	if (fetch_refs(transport, ref_map)) {
		free_refs(ref_map);
		retcode = 1;
		goto cleanup;
	}
	free_refs(ref_map);

	/* if neither --no-tags nor --tags was specified, do automated tag
	 * following ... */
	if (tags == TAGS_DEFAULT && autotags) {
		struct ref **tail = &ref_map;
		ref_map = NULL;
		find_non_local_tags(transport, &ref_map, &tail);
		if (ref_map)
			backfill_tags(transport, ref_map);
		free_refs(ref_map);
	}

 cleanup:
	string_list_clear(&existing_refs, 1);
	return retcode;
}
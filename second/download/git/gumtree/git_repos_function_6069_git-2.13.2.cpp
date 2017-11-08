static int get_push_ref_states(const struct ref *remote_refs,
	struct ref_states *states)
{
	struct remote *remote = states->remote;
	struct ref *ref, *local_refs, *push_map;
	if (remote->mirror)
		return 0;

	local_refs = get_local_heads();
	push_map = copy_ref_list(remote_refs);

	match_push_refs(local_refs, &push_map, remote->push_refspec_nr,
			remote->push_refspec, MATCH_REFS_NONE);

	states->push.strdup_strings = 1;
	for (ref = push_map; ref; ref = ref->next) {
		struct string_list_item *item;
		struct push_info *info;

		if (!ref->peer_ref)
			continue;
		oidcpy(&ref->new_oid, &ref->peer_ref->new_oid);

		item = string_list_append(&states->push,
					  abbrev_branch(ref->peer_ref->name));
		item->util = xcalloc(1, sizeof(struct push_info));
		info = item->util;
		info->forced = ref->force;
		info->dest = xstrdup(abbrev_branch(ref->name));

		if (is_null_oid(&ref->new_oid)) {
			info->status = PUSH_STATUS_DELETE;
		} else if (!oidcmp(&ref->old_oid, &ref->new_oid))
			info->status = PUSH_STATUS_UPTODATE;
		else if (is_null_oid(&ref->old_oid))
			info->status = PUSH_STATUS_CREATE;
		else if (has_object_file(&ref->old_oid) &&
			 ref_newer(&ref->new_oid, &ref->old_oid))
			info->status = PUSH_STATUS_FASTFORWARD;
		else
			info->status = PUSH_STATUS_OUTOFDATE;
	}
	free_refs(local_refs);
	free_refs(push_map);
	return 0;
}
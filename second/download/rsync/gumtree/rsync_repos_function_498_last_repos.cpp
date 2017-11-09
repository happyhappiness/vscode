static uchar recv_ida_entries(int f, ida_entries *ent)
{
	uchar computed_mask_bits = 0;
	int i, count = read_varint(f);

	if (count) {
		if (!(ent->idas = new_array(id_access, count)))
			out_of_memory("recv_ida_entries");
	} else
		ent->idas = NULL;

	ent->count = count;

	for (i = 0; i < count; i++) {
		uchar has_name;
		id_t id = read_varint(f);
		uint32 access = recv_acl_access(f, &has_name);

		if (has_name) {
			if (access & NAME_IS_USER)
				id = recv_user_name(f, id);
			else
				id = recv_group_name(f, id, NULL);
		} else if (access & NAME_IS_USER) {
			if (inc_recurse && am_root && !numeric_ids)
				id = match_uid(id);
		} else {
			if (inc_recurse && (!am_root || !numeric_ids))
				id = match_gid(id, NULL);
		}

		ent->idas[i].id = id;
		ent->idas[i].access = access;
		computed_mask_bits |= access;
	}

	return computed_mask_bits & ~NO_ENTRY;
}
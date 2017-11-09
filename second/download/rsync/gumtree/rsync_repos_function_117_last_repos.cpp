gid_t match_gid(gid_t gid, uint16 *flags_ptr)
{
	static struct idlist *last = NULL;
	struct idlist *list;

	if (last && gid == last->id)
		list = last;
	else {
		for (list = gidlist; list; list = list->next) {
			if (list->id == gid)
				break;
		}
		if (!list)
			list = recv_add_id(&gidlist, gidmap, gid, NULL);
		last = list;
	}

	if (flags_ptr && list->flags & FLAG_SKIP_GROUP)
		*flags_ptr |= FLAG_SKIP_GROUP;
	return list->id2;
}
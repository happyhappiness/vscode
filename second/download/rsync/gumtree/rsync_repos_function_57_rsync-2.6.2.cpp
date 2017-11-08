static gid_t match_gid(gid_t gid)
{
	static gid_t last_in = GID_NONE, last_out = GID_NONE;
	struct idlist *list;

	if (gid == GID_NONE)
		return GID_NONE;

	if (gid == last_in)
		return last_out;

	last_in = gid;

	for (list = gidlist; list; list = list->next) {
		if (list->id == (int)gid)
			return last_out = (gid_t)list->id2;
	}

	list = recv_add_gid(gid, NULL);
	return last_out = list->id2;
}
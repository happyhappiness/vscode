void add_gid(gid_t gid)
{
	struct idlist *list;

	if (gid == 0)	/* don't map root */
		return;

	for (list = gidlist; list; list = list->next) {
		if (list->id == (int)gid)
			return;
	}

	add_to_list(&gidlist, (int)gid, gid_to_name(gid), 0);
}
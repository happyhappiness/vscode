void add_gid(gid_t gid)
{
	struct idlist *list = gidlist;
	char *name;

	if (numeric_ids) return;

	/* don't map root */
	if (gid==0) return;

	if (!list) {
		if (!(name = gid_to_name(gid))) return;
		gidlist = add_list((int)gid, name);
		return;
	}

	while (list->next) {
		if (list->id == (int)gid) return;
		list = list->next;
	}

	if (list->id == (int)gid) return;

	if (!(name = gid_to_name(gid))) return;

	list->next = add_list((int)gid, name);
}
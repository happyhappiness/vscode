const char *add_gid(gid_t gid)
{
	struct idlist *list;
	struct idlist *node;

	if (gid == 0)	/* don't map root */
		return NULL;

	for (list = gidlist; list; list = list->next) {
		if (list->id == gid)
			return NULL;
	}

	node = add_to_list(&gidlist, gid, gid_to_name(gid), 0, 0);
	return node->name;
}
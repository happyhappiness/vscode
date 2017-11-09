const char *add_gid(gid_t gid)
{
	struct idlist *list;
	struct idlist *node;
	union name_or_id noiu;

	if (gid == 0)	/* don't map root */
		return NULL;

	for (list = gidlist; list; list = list->next) {
		if (list->id == gid)
			return NULL;
	}

	noiu.name = gid_to_group(gid);
	node = add_to_list(&gidlist, gid, noiu, 0, 0);
	return node->u.name;
}
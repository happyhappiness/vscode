const char *add_uid(uid_t uid)
{
	struct idlist *list;
	struct idlist *node;

	if (uid == 0)	/* don't map root */
		return NULL;

	for (list = uidlist; list; list = list->next) {
		if (list->id == uid)
			return NULL;
	}

	node = add_to_list(&uidlist, uid, uid_to_name(uid), 0, 0);
	return node->name;
}
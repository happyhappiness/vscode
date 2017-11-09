const char *add_uid(uid_t uid)
{
	struct idlist *list;
	struct idlist *node;
	union name_or_id noiu;

	if (uid == 0)	/* don't map root */
		return NULL;

	for (list = uidlist; list; list = list->next) {
		if (list->id == uid)
			return NULL;
	}

	noiu.name = uid_to_user(uid);
	node = add_to_list(&uidlist, uid, noiu, 0, 0);
	return node->u.name;
}
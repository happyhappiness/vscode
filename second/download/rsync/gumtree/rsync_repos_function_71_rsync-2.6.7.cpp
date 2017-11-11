void add_uid(uid_t uid)
{
	struct idlist *list;

	if (uid == 0)	/* don't map root */
		return;

	for (list = uidlist; list; list = list->next) {
		if (list->id == (int)uid)
			return;
	}

	add_to_list(&uidlist, (int)uid, uid_to_name(uid), 0);
}
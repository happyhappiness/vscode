void add_uid(uid_t uid)
{
	struct idlist *list = uidlist;
	char *name;

	if (numeric_ids) return;

	/* don't map root */
	if (uid==0) return;

	if (!list) {
		if (!(name = uid_to_name(uid))) return;
		uidlist = add_list((int)uid, name);
		return;
	}

	while (list->next) {
		if (list->id == (int)uid) return;
		list = list->next;
	}

	if (list->id == (int)uid) return;

	if (!(name = uid_to_name(uid))) return;

	list->next = add_list((int)uid, name);
}
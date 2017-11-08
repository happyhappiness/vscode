static uid_t match_uid(uid_t uid)
{
	static uid_t last_in, last_out;
	struct idlist *list;

	if (uid == 0)
		return 0;

	if (uid == last_in)
		return last_out;

	last_in = uid;

	for (list = uidlist; list; list = list->next) {
		if (list->id == (int)uid)
			return last_out = (uid_t)list->id2;
	}

	return last_out = uid;
}
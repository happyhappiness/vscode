static uid_t match_uid(uid_t uid)
{
	static uid_t last_in, last_out;
	struct idlist *list = uidlist;

	if (uid == last_in) return last_out;

	last_in = uid;

	while (list) {
		if (list->id == (int)uid) {
			last_out = (uid_t)list->id2;
			return last_out;
		}
		list = list->next;
	}
	
	last_out = uid;
	return last_out;
}
uid_t match_uid(uid_t uid)
{
	static struct idlist *last = NULL;
	struct idlist *list;

	if (last && uid == last->id)
		return last->id2;

	for (list = uidlist; list; list = list->next) {
		if (list->id == uid)
			break;
	}

	if (!list)
		list = recv_add_id(&uidlist, uidmap, uid, NULL);
	last = list;

	return list->id2;
}
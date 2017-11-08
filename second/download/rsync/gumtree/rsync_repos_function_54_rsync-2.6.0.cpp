static gid_t match_gid(gid_t gid)
{
	static gid_t last_in, last_out;
	struct idlist *list = gidlist;

	if (gid == last_in) return last_out;

	last_in = gid;

	while (list) {
		if (list->id == (int)gid) {
			last_out = (gid_t)list->id2;
			return last_out;
		}
		list = list->next;
	}
	
	if (am_root)
		last_out = gid;
	else
		last_out = (gid_t) -1;
	return last_out;
}
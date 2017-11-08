void send_uid_list(int f)
{
	struct idlist *list;

	if (numeric_ids) return;

	if (preserve_uid) {
		/* we send sequences of uid/byte-length/name */
		list = uidlist;
		while (list) {
			int len = strlen(list->name);
			write_int(f, list->id);
			write_byte(f, len);
			write_buf(f, list->name, len);
			list = list->next;
		}

		/* terminate the uid list with a 0 uid. We explicitly exclude
		   0 from the list */
		write_int(f, 0);
	}

	if (preserve_gid) {
		list = gidlist;
		while (list) {
			int len = strlen(list->name);
			write_int(f, list->id);
			write_byte(f, len);
			write_buf(f, list->name, len);
			list = list->next;
		}
		write_int(f, 0);
	}
}
void send_uid_list(int f)
{
	struct idlist *list;

	if (numeric_ids)
		return;

	if (preserve_uid) {
		int len;
		/* we send sequences of uid/byte-length/name */
		for (list = uidlist; list; list = list->next) {
			if (!list->name)
				continue;
			len = strlen(list->name);
			write_int(f, list->id);
			write_byte(f, len);
			write_buf(f, list->name, len);
		}

		/* terminate the uid list with a 0 uid. We explicitly exclude
		 * 0 from the list */
		write_int(f, 0);
	}

	if (preserve_gid) {
		int len;
		for (list = gidlist; list; list = list->next) {
			if (!list->name)
				continue;
			len = strlen(list->name);
			write_int(f, list->id);
			write_byte(f, len);
			write_buf(f, list->name, len);
		}
		write_int(f, 0);
	}
}
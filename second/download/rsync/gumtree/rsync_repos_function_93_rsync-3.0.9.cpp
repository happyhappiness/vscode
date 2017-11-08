void send_id_list(int f)
{
	struct idlist *list;

	if (preserve_uid || preserve_acls) {
		int len;
		/* we send sequences of uid/byte-length/name */
		for (list = uidlist; list; list = list->next) {
			if (!list->name)
				continue;
			len = strlen(list->name);
			write_varint30(f, list->id);
			write_byte(f, len);
			write_buf(f, list->name, len);
		}

		/* terminate the uid list with a 0 uid. We explicitly exclude
		 * 0 from the list */
		write_varint30(f, 0);
	}

	if (preserve_gid || preserve_acls) {
		int len;
		for (list = gidlist; list; list = list->next) {
			if (!list->name)
				continue;
			len = strlen(list->name);
			write_varint30(f, list->id);
			write_byte(f, len);
			write_buf(f, list->name, len);
		}
		write_varint30(f, 0);
	}
}
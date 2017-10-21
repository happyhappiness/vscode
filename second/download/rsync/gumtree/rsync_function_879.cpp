void recv_uid_list(int f, struct file_list *flist)
{
	int id, i;
	char *name;

	if (preserve_uid && !numeric_ids) {
		/* read the uid list */
		while ((id = read_int(f)) != 0) {
			int len = read_byte(f);
			name = new_array(char, len+1);
			if (!name)
				out_of_memory("recv_uid_list");
			read_sbuf(f, name, len);
			recv_add_uid(id, name); /* node keeps name's memory */
		}
	}

	if (preserve_gid && !numeric_ids) {
		/* read the gid list */
		while ((id = read_int(f)) != 0) {
			int len = read_byte(f);
			name = new_array(char, len+1);
			if (!name)
				out_of_memory("recv_uid_list");
			read_sbuf(f, name, len);
			recv_add_gid(id, name); /* node keeps name's memory */
		}
	}

	/* Now convert all the uids/gids from sender values to our values. */
	if (am_root && preserve_uid && !numeric_ids) {
		for (i = 0; i < flist->count; i++)
			flist->files[i]->uid = match_uid(flist->files[i]->uid);
	}
	if (preserve_gid && (!am_root || !numeric_ids)) {
		for (i = 0; i < flist->count; i++)
			flist->files[i]->gid = match_gid(flist->files[i]->gid);
	}
}
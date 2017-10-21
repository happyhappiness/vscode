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

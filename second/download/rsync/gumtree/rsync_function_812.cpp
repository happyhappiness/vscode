int recv_xattr_request(struct file_struct *file, int f_in)
{
	item_list *lst = rsync_xal_l.items;
	char *old_datum, *name;
	rsync_xa *rxa;
	int rel_pos, cnt, num, got_xattr_data = 0;

	if (F_XATTR(file) < 0) {
		rprintf(FERROR, "recv_xattr_request: internal data error!\n");
		exit_cleanup(RERR_STREAMIO);
	}
	lst += F_XATTR(file);

	cnt = lst->count;
	rxa = lst->items;
	num = 0;
	while ((rel_pos = read_varint(f_in)) != 0) {
		num += rel_pos;
		while (cnt && rxa->num < num) {
		    rxa++;
		    cnt--;
		}
		if (!cnt || rxa->num != num) {
			rprintf(FERROR, "[%s] could not find xattr #%d for %s\n",
				who_am_i(), num, f_name(file, NULL));
			exit_cleanup(RERR_STREAMIO);
		}
		if (rxa->datum_len <= MAX_FULL_DATUM || rxa->datum[0] != XSTATE_ABBREV) {
			rprintf(FERROR, "[%s] internal abbrev error!\n", who_am_i());
			exit_cleanup(RERR_STREAMIO);
		}

		if (am_sender) {
			rxa->datum[0] = XSTATE_TODO;
			continue;
		}

		old_datum = rxa->datum;
		rxa->datum_len = read_varint(f_in);

		if (rxa->name_len + rxa->datum_len < rxa->name_len)
			out_of_memory("recv_xattr_request"); /* overflow */
		rxa->datum = new_array(char, rxa->datum_len + rxa->name_len);
		if (!rxa->datum)
			out_of_memory("recv_xattr_request");
		name = rxa->datum + rxa->datum_len;
		memcpy(name, rxa->name, rxa->name_len);
		rxa->name = name;
		free(old_datum);
		read_buf(f_in, rxa->datum, rxa->datum_len);
		got_xattr_data = 1;
	}

	return got_xattr_data;
}
	if (preserve_gid) {
		/* and the gid list */
		list = gidlist;
		id = read_int(f);
		while (id != 0) {
			int len = read_byte(f);
			name = (char *)malloc(len);
			if (!name) out_of_memory("recv_uid_list");
			read_buf(f, name, len);
			if (!list) {
				gidlist = add_list(id, name);
				list = gidlist;
			} else {
				list->next = add_list(id, name);
				list = list->next;

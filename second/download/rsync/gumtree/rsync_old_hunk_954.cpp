		if (len < 4*4 || len != (size_t)cnt*(4+4) + 4*4) {
			free(buf);
			return -1;
		}

		racl->user_obj = IVAL(buf, 0);
		racl->group_obj = IVAL(buf, 4);
		racl->mask_obj = IVAL(buf, 8);
		racl->other_obj = IVAL(buf, 12);

		if (cnt) {
			char *bp = buf + 4*4;
			id_access *ida;
			if (!(ida = racl->names.idas = new_array(id_access, cnt)))
				out_of_memory("get_rsync_acl");

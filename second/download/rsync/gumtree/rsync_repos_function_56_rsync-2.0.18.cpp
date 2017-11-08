void recv_uid_list(int f, struct file_list *flist)
{
	int id, i;
	char *name;
	struct idlist *list;

	if (numeric_ids) return;

	if (preserve_uid) {
		/* read the uid list */
		list = uidlist;
		id = read_int(f);
		while (id != 0) {
			int len = read_byte(f);
			name = (char *)malloc(len+1);
			if (!name) out_of_memory("recv_uid_list");
			read_sbuf(f, name, len);
			if (!list) {
				uidlist = add_list(id, name);
				list = uidlist;
			} else {
				list->next = add_list(id, name);
				list = list->next;
			}
			list->id2 = map_uid(id, name);
			free(name);
			id = read_int(f);
		}
	}


	if (preserve_gid) {
		/* and the gid list */
		list = gidlist;
		id = read_int(f);
		while (id != 0) {
			int len = read_byte(f);
			name = (char *)malloc(len+1);
			if (!name) out_of_memory("recv_uid_list");
			read_sbuf(f, name, len);
			if (!list) {
				gidlist = add_list(id, name);
				list = gidlist;
			} else {
				list->next = add_list(id, name);
				list = list->next;
			}
			list->id2 = map_gid(id, name);
			free(name);
			id = read_int(f);
		}
	}

	if (!uidlist && !gidlist) return;

	/* now convert the uid/gid of all files in the list to the mapped
	   uid/gid */
	for (i=0;i<flist->count;i++) {
		if (preserve_uid && flist->files[i]->uid != 0) {
			flist->files[i]->uid = match_uid(flist->files[i]->uid);
		}
		if (preserve_gid && flist->files[i]->gid != 0) {
			flist->files[i]->gid = match_gid(flist->files[i]->gid);
		}
	}
}
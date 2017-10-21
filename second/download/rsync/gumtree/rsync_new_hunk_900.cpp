	if (uid == last_in)
		return last_out;

	last_in = uid;

	for (list = uidlist; list; list = list->next) {
		if (list->id == uid)
			return last_out = list->id2;
	}

	return last_out = uid;
}

gid_t match_gid(gid_t gid, uint16 *flags_ptr)
{
	static struct idlist *last = NULL;
	struct idlist *list;

	if (last && gid == last->id)
		list = last;
	else {
		for (list = gidlist; list; list = list->next) {
			if (list->id == gid)
				break;
		}
		if (!list)
			list = recv_add_gid(gid, NULL);
		last = list;
	}

	if (flags_ptr && list->flags & FLAG_SKIP_GROUP)
		*flags_ptr |= FLAG_SKIP_GROUP;
	return list->id2;
}

/* Add a uid to the list of uids.  Only called on sending side. */
const char *add_uid(uid_t uid)
{
	struct idlist *list;
	struct idlist *node;

	if (uid == 0)	/* don't map root */
		return NULL;

	for (list = uidlist; list; list = list->next) {
		if (list->id == uid)
			return NULL;
	}

	node = add_to_list(&uidlist, uid, uid_to_name(uid), 0, 0);
	return node->name;
}

/* Add a gid to the list of gids.  Only called on sending side. */
const char *add_gid(gid_t gid)
{
	struct idlist *list;
	struct idlist *node;

	if (gid == 0)	/* don't map root */
		return NULL;

	for (list = gidlist; list; list = list->next) {
		if (list->id == gid)
			return NULL;
	}

	node = add_to_list(&gidlist, gid, gid_to_name(gid), 0, 0);
	return node->name;
}

/* send a complete uid/gid mapping to the peer */
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

uid_t recv_user_name(int f, uid_t uid)
{
	struct idlist *node;
	int len = read_byte(f);
	char *name = new_array(char, len+1);
	if (!name)
		out_of_memory("recv_user_name");
	read_sbuf(f, name, len);
	if (numeric_ids < 0) {
		free(name);
		name = NULL;
	}
	node = recv_add_uid(uid, name); /* node keeps name's memory */
	return node->id2;
}

gid_t recv_group_name(int f, gid_t gid, uint16 *flags_ptr)
{
	struct idlist *node;
	int len = read_byte(f);
	char *name = new_array(char, len+1);
	if (!name)
		out_of_memory("recv_group_name");
	read_sbuf(f, name, len);
	if (numeric_ids < 0) {
		free(name);
		name = NULL;
	}
	node = recv_add_gid(gid, name); /* node keeps name's memory */
	if (flags_ptr && node->flags & FLAG_SKIP_GROUP)
		*flags_ptr |= FLAG_SKIP_GROUP;
	return node->id2;
}

/* recv a complete uid/gid mapping from the peer and map the uid/gid
 * in the file list to local names */
void recv_id_list(int f, struct file_list *flist)
{
	id_t id;
	int i;

	if ((preserve_uid || preserve_acls) && numeric_ids <= 0) {
		/* read the uid list */
		while ((id = read_varint30(f)) != 0)
			recv_user_name(f, id);
	}

	if ((preserve_gid || preserve_acls) && numeric_ids <= 0) {
		/* read the gid list */
		while ((id = read_varint30(f)) != 0)
			recv_group_name(f, id, NULL);
	}

	/* Now convert all the uids/gids from sender values to our values. */
#ifdef SUPPORT_ACLS
	if (preserve_acls && !numeric_ids)
		match_acl_ids();
#endif
	if (am_root && preserve_uid && !numeric_ids) {
		for (i = 0; i < flist->used; i++)
			F_OWNER(flist->files[i]) = match_uid(F_OWNER(flist->files[i]));
	}
	if (preserve_gid && (!am_root || !numeric_ids)) {
		for (i = 0; i < flist->used; i++) {
			F_GROUP(flist->files[i]) = match_gid(F_GROUP(flist->files[i]),
							     &flist->files[i]->flags);
		}
	}
}

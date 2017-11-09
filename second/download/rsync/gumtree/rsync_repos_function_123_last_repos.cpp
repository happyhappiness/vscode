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
	if (preserve_acls && (!numeric_ids || usermap || groupmap))
		match_acl_ids();
#endif
	if (am_root && preserve_uid && (!numeric_ids || usermap)) {
		for (i = 0; i < flist->used; i++)
			F_OWNER(flist->files[i]) = match_uid(F_OWNER(flist->files[i]));
	}
	if (preserve_gid && (!am_root || !numeric_ids || groupmap)) {
		for (i = 0; i < flist->used; i++) {
			F_GROUP(flist->files[i]) = match_gid(F_GROUP(flist->files[i]),
							     &flist->files[i]->flags);
		}
	}
}
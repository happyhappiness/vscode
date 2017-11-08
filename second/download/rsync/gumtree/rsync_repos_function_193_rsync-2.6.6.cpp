static int unchanged_attrs(struct file_struct *file, STRUCT_STAT *st)
{
	if (preserve_perms
	 && (st->st_mode & CHMOD_BITS) != (file->mode & CHMOD_BITS))
		return 0;

	if (am_root && preserve_uid && st->st_uid != file->uid)
		return 0;

	if (preserve_gid && file->gid != GID_NONE && st->st_gid != file->gid)
		return 0;

	return 1;
}
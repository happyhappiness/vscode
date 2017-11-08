static int fsck_tree(struct tree *item, int strict, fsck_error error_func)
{
	int retval;
	int has_null_sha1 = 0;
	int has_full_path = 0;
	int has_empty_name = 0;
	int has_dot = 0;
	int has_dotdot = 0;
	int has_dotgit = 0;
	int has_zero_pad = 0;
	int has_bad_modes = 0;
	int has_dup_entries = 0;
	int not_properly_sorted = 0;
	struct tree_desc desc;
	unsigned o_mode;
	const char *o_name;

	init_tree_desc(&desc, item->buffer, item->size);

	o_mode = 0;
	o_name = NULL;

	while (desc.size) {
		unsigned mode;
		const char *name;
		const unsigned char *sha1;

		sha1 = tree_entry_extract(&desc, &name, &mode);

		has_null_sha1 |= is_null_sha1(sha1);
		has_full_path |= !!strchr(name, '/');
		has_empty_name |= !*name;
		has_dot |= !strcmp(name, ".");
		has_dotdot |= !strcmp(name, "..");
		has_dotgit |= (!strcmp(name, ".git") ||
			       is_hfs_dotgit(name) ||
			       is_ntfs_dotgit(name));
		has_zero_pad |= *(char *)desc.buffer == '0';
		update_tree_entry(&desc);

		switch (mode) {
		/*
		 * Standard modes..
		 */
		case S_IFREG | 0755:
		case S_IFREG | 0644:
		case S_IFLNK:
		case S_IFDIR:
		case S_IFGITLINK:
			break;
		/*
		 * This is nonstandard, but we had a few of these
		 * early on when we honored the full set of mode
		 * bits..
		 */
		case S_IFREG | 0664:
			if (!strict)
				break;
		default:
			has_bad_modes = 1;
		}

		if (o_name) {
			switch (verify_ordered(o_mode, o_name, mode, name)) {
			case TREE_UNORDERED:
				not_properly_sorted = 1;
				break;
			case TREE_HAS_DUPS:
				has_dup_entries = 1;
				break;
			default:
				break;
			}
		}

		o_mode = mode;
		o_name = name;
	}

	retval = 0;
	if (has_null_sha1)
		retval += error_func(&item->object, FSCK_WARN, "contains entries pointing to null sha1");
	if (has_full_path)
		retval += error_func(&item->object, FSCK_WARN, "contains full pathnames");
	if (has_empty_name)
		retval += error_func(&item->object, FSCK_WARN, "contains empty pathname");
	if (has_dot)
		retval += error_func(&item->object, FSCK_WARN, "contains '.'");
	if (has_dotdot)
		retval += error_func(&item->object, FSCK_WARN, "contains '..'");
	if (has_dotgit)
		retval += error_func(&item->object, FSCK_WARN, "contains '.git'");
	if (has_zero_pad)
		retval += error_func(&item->object, FSCK_WARN, "contains zero-padded file modes");
	if (has_bad_modes)
		retval += error_func(&item->object, FSCK_WARN, "contains bad file modes");
	if (has_dup_entries)
		retval += error_func(&item->object, FSCK_ERROR, "contains duplicate file entries");
	if (not_properly_sorted)
		retval += error_func(&item->object, FSCK_ERROR, "not properly sorted");
	return retval;
}
static int path_is_beyond_symlink_1(struct strbuf *name)
{
	do {
		unsigned int change;

		while (--name->len && name->buf[name->len] != '/')
			; /* scan backwards */
		if (!name->len)
			break;
		name->buf[name->len] = '\0';
		change = check_symlink_changes(name->buf);
		if (change & SYMLINK_IN_RESULT)
			return 1;
		if (change & SYMLINK_GOES_AWAY)
			/*
			 * This cannot be "return 0", because we may
			 * see a new one created at a higher level.
			 */
			continue;

		/* otherwise, check the preimage */
		if (check_index) {
			struct cache_entry *ce;

			ce = cache_file_exists(name->buf, name->len, ignore_case);
			if (ce && S_ISLNK(ce->ce_mode))
				return 1;
		} else {
			struct stat st;
			if (!lstat(name->buf, &st) && S_ISLNK(st.st_mode))
				return 1;
		}
	} while (1);
	return 0;
}
const char *resolve_ref_unsafe(const char *refname, unsigned char *sha1, int reading, int *flag)
{
	int depth = MAXDEPTH;
	ssize_t len;
	char buffer[256];
	static char refname_buffer[256];

	if (flag)
		*flag = 0;

	if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL))
		return NULL;

	for (;;) {
		char path[PATH_MAX];
		struct stat st;
		char *buf;
		int fd;

		if (--depth < 0)
			return NULL;

		git_snpath(path, sizeof(path), "%s", refname);

		/*
		 * We might have to loop back here to avoid a race
		 * condition: first we lstat() the file, then we try
		 * to read it as a link or as a file.  But if somebody
		 * changes the type of the file (file <-> directory
		 * <-> symlink) between the lstat() and reading, then
		 * we don't want to report that as an error but rather
		 * try again starting with the lstat().
		 */
	stat_ref:
		if (lstat(path, &st) < 0) {
			if (errno == ENOENT)
				return handle_missing_loose_ref(refname, sha1,
								reading, flag);
			else
				return NULL;
		}

		/* Follow "normalized" - ie "refs/.." symlinks by hand */
		if (S_ISLNK(st.st_mode)) {
			len = readlink(path, buffer, sizeof(buffer)-1);
			if (len < 0) {
				if (errno == ENOENT || errno == EINVAL)
					/* inconsistent with lstat; retry */
					goto stat_ref;
				else
					return NULL;
			}
			buffer[len] = 0;
			if (starts_with(buffer, "refs/") &&
					!check_refname_format(buffer, 0)) {
				strcpy(refname_buffer, buffer);
				refname = refname_buffer;
				if (flag)
					*flag |= REF_ISSYMREF;
				continue;
			}
		}

		/* Is it a directory? */
		if (S_ISDIR(st.st_mode)) {
			errno = EISDIR;
			return NULL;
		}

		/*
		 * Anything else, just open it and try to use it as
		 * a ref
		 */
		fd = open(path, O_RDONLY);
		if (fd < 0) {
			if (errno == ENOENT)
				/* inconsistent with lstat; retry */
				goto stat_ref;
			else
				return NULL;
		}
		len = read_in_full(fd, buffer, sizeof(buffer)-1);
		close(fd);
		if (len < 0)
			return NULL;
		while (len && isspace(buffer[len-1]))
			len--;
		buffer[len] = '\0';

		/*
		 * Is it a symbolic ref?
		 */
		if (!starts_with(buffer, "ref:")) {
			/*
			 * Please note that FETCH_HEAD has a second
			 * line containing other data.
			 */
			if (get_sha1_hex(buffer, sha1) ||
			    (buffer[40] != '\0' && !isspace(buffer[40]))) {
				if (flag)
					*flag |= REF_ISBROKEN;
				return NULL;
			}
			return refname;
		}
		if (flag)
			*flag |= REF_ISSYMREF;
		buf = buffer + 4;
		while (isspace(*buf))
			buf++;
		if (check_refname_format(buf, REFNAME_ALLOW_ONELEVEL)) {
			if (flag)
				*flag |= REF_ISBROKEN;
			return NULL;
		}
		refname = strcpy(refname_buffer, buf);
	}
}
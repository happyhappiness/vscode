const char *resolve_ref_unsafe(const char *refname, int resolve_flags, unsigned char *sha1, int *flags)
{
	int depth = MAXDEPTH;
	ssize_t len;
	char buffer[256];
	static char refname_buffer[256];
	int bad_name = 0;

	if (flags)
		*flags = 0;

	if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
		if (flags)
			*flags |= REF_BAD_NAME;

		if (!(resolve_flags & RESOLVE_REF_ALLOW_BAD_NAME) ||
		    !refname_is_safe(refname)) {
			errno = EINVAL;
			return NULL;
		}
		/*
		 * dwim_ref() uses REF_ISBROKEN to distinguish between
		 * missing refs and refs that were present but invalid,
		 * to complain about the latter to stderr.
		 *
		 * We don't know whether the ref exists, so don't set
		 * REF_ISBROKEN yet.
		 */
		bad_name = 1;
	}
	for (;;) {
		char path[PATH_MAX];
		struct stat st;
		char *buf;
		int fd;

		if (--depth < 0) {
			errno = ELOOP;
			return NULL;
		}

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
			if (errno != ENOENT)
				return NULL;
			if (resolve_missing_loose_ref(refname, resolve_flags,
						      sha1, flags))
				return NULL;
			if (bad_name) {
				hashclr(sha1);
				if (flags)
					*flags |= REF_ISBROKEN;
			}
			return refname;
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
				if (flags)
					*flags |= REF_ISSYMREF;
				if (resolve_flags & RESOLVE_REF_NO_RECURSE) {
					hashclr(sha1);
					return refname;
				}
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
		if (len < 0) {
			int save_errno = errno;
			close(fd);
			errno = save_errno;
			return NULL;
		}
		close(fd);
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
				if (flags)
					*flags |= REF_ISBROKEN;
				errno = EINVAL;
				return NULL;
			}
			if (bad_name) {
				hashclr(sha1);
				if (flags)
					*flags |= REF_ISBROKEN;
			}
			return refname;
		}
		if (flags)
			*flags |= REF_ISSYMREF;
		buf = buffer + 4;
		while (isspace(*buf))
			buf++;
		refname = strcpy(refname_buffer, buf);
		if (resolve_flags & RESOLVE_REF_NO_RECURSE) {
			hashclr(sha1);
			return refname;
		}
		if (check_refname_format(buf, REFNAME_ALLOW_ONELEVEL)) {
			if (flags)
				*flags |= REF_ISBROKEN;

			if (!(resolve_flags & RESOLVE_REF_ALLOW_BAD_NAME) ||
			    !refname_is_safe(buf)) {
				errno = EINVAL;
				return NULL;
			}
			bad_name = 1;
		}
	}
}